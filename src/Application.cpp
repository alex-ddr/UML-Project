#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <map>
#include <algorithm>
#include <cmath>
#include "Application.h"
#include "Mesure.h"
#include "Parser.h"
using namespace std;

bool Application::chargerDonnees(const std::string &cheminFichierSensors, const string &cheminFichierUsers, const std::string &cheminFichierAttributs, const string &cheminFichierMesures) {

    listeTousLesCapteurs = Parser::chargerCapteurs(cheminFichierSensors, cheminFichierUsers);
    Parser :: chargerMesures(cheminFichierMesures, cheminFichierAttributs, listeTousLesCapteurs);
}



// fonction pour calculer la distance euclidienne entre deux points
float distance(float lat1, float lon1, float lat2, float lon2)
{
    return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

int getIndiceFromValue(float value, const vector<pair<float, float>> &ranges)
{
    for (size_t i = 0; i < ranges.size(); ++i)
    {
        if (value >= ranges[i].first && value <= ranges[i].second)
            return static_cast<int>(i) + 1;
    }
    // Valeurs hors norme : retourne 10 (Très mauvais)
    return 10;
}

map<string, int> calculerIndicesATMO(const map<string, float> &moyennesParGaz)
{
    // Ranges ATMO pour chaque polluant, indexés de 1 à 10
    map<string, vector<pair<float, float>>> seuils = {
        {"O3", {{0, 29}, {30, 54}, {55, 79}, {80, 104}, {105, 129}, {130, 149}, {150, 179}, {180, 209}, {210, 239}, {240, 1e9}}},
        {"SO2", {{0, 39}, {40, 79}, {80, 119}, {120, 159}, {160, 199}, {200, 249}, {250, 299}, {300, 399}, {400, 499}, {500, 1e9}}},
        {"NO2", {{0, 29}, {30, 54}, {55, 84}, {85, 109}, {110, 134}, {135, 164}, {165, 199}, {200, 274}, {275, 399}, {400, 1e9}}},
        {"PM10", {{0, 6}, {7, 13}, {14, 20}, {21, 27}, {28, 34}, {35, 41}, {42, 49}, {50, 64}, {65, 79}, {80, 1e9}}}};

    map<string, int> indices;
    for (auto it = moyennesParGaz.begin(); it != moyennesParGaz.end(); ++it)
    {
        const string &gaz = it->first;
        float valeur = it->second;
        if (seuils.count(gaz))
        {
            indices[gaz] = getIndiceFromValue(valeur, seuils[gaz]);
        }
        else
        {
            indices[gaz] = -1; // gaz inconnu
        }
    }
    return indices;
}

map<string, int> Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    /*
    Calcule la moyenne de la qualité de l'air pour différents gaz sur une période donnée et dans une zone géographique.

    Arguments d'entrée :
    - latitude : latitude du centre de la zone d'étude (float)
    - longitude : longitude du centre de la zone d'étude (float)
    - debut : timestamp de début de la période (time_t)
    - fin : timestamp de fin de la période (time_t). Si nul (0), la période est d'une journée à partir de debut.
    - perimetre : rayon de la zone d'étude autour des coordonnées, en unités compatibles (float)

    Retour :
    - map<string, float> : indice ATMO des concentrations mesurées pour chaque gaz ("O3", "SO2", "NO2", "PM10")
    */

    map<string, float> moyennesParGaz = {
        {"O3", 0.0},
        {"SO2", 0.0},
        {"NO2", 0.0},
        {"PM10", 0.0}};

    string gaz[4] = {"O3", "SO2", "NO2", "PM10"};
    int nbCapteurs[4] = {0};
    float moyennesTotales[4] = {0};

    if (!fin)
    {
        fin = debut + 24 * 3600;
    } // si pas de fin définie, alors par défaut la fin est le jour de début + 1 (période d'un jour par défaut)

    for (const Capteur &c : listeTousLesCapteurs)
    {

        // on ne prend que les capteurs dans la zone géographique circulaire donnée
        if (distance(latitude, longitude, c.getLatitude(), c.getLongitude()) > perimetre)
            continue;

        float moyennes[4] = {0};
        int nbMesures[4] = {0};

        for (const Mesure &m : c.getListeMesures())
        {

            // Pour chaque mesure du capteur,
            // qui est bien incluse dans l'intervalle de temps souhaité,
            // on regarde à quel gaz elle conrrepond parmi O3, SO2, NO2 et PM10
            // et pour ce gaz là, on incrémente le nombre de mesures
            // et on ajoute la mesure à sa moyenne

            if (debut < m.getTimestamp() && m.getTimestamp() < fin)
            {

                time_t t = m.getTimestamp();
                if (t >= debut && t <= fin)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        if (m.getAttribut().attributId == gaz[i])
                        {
                            moyennes[i] += m.getValeur();
                            ++nbMesures[i];
                        }
                    }
                }
            }

            // on calcule les moyennes (pour chaque gaz) pour ce capteur
            for (int i = 0; i < 4; ++i)
            {
                if (nbMesures[i] > 0)
                {
                    moyennes[i] /= nbMesures[i];
                    moyennesTotales[i] += moyennes[i];
                    ++nbCapteurs[i];
                }
            }
        }
    }

    // Enfin, la moyenne finale par gaz (moyenne des moyennes de tous les capteurs)
    for (int i = 0; i < 4; ++i)
    {
        if (nbCapteurs[i] > 0)
            moyennesTotales[i] /= nbCapteurs[i];
        moyennesParGaz[gaz[i]] = moyennesTotales[i];
    }

    return calculerIndicesATMO(moyennesParGaz);
}

vector<pair<Capteur, float>> Application::listerCapteursSimilaires(Capteur &capteur) const
{
    // 1) Date max
    auto mesuresRefFull = capteur.getListeMesures();
    time_t dateMax = 0;
    for (auto &m : mesuresRefFull)
        if (m.getTimestamp() > dateMax)
            dateMax = m.getTimestamp();

    // 2) Date début
    time_t dateDebut = dateMax - 7 * 24 * 3600;

    // 3) Filtrer les mesures de référence
    vector<Mesure> mesuresRef;
    for (auto &m : mesuresRefFull)
        if (m.getTimestamp() >= dateDebut && m.getTimestamp() <= dateMax)
            mesuresRef.push_back(m);

    // 4) Prépare le résultat
    vector<pair<Capteur, float>> capteursSim;

    // 5) Parcours tous les capteurs
    for (auto &autre : listeTousLesCapteurs)
    {
        if (autre == capteur)
            continue;
        // si on gère la fiabilité RAJOUTER UN TRUC
        if (!autre.isConfiance())
            continue; // on ne prend pas les capteurs non fiables
        // 5b) filtre ses mesures
        vector<Mesure> mesuresAutre;
        for (auto &m : autre.getListeMesures())
            if (m.getTimestamp() >= dateDebut && m.getTimestamp() <= dateMax)
                mesuresAutre.push_back(m);

        // 5c) calcul de la distance
        float somme2 = 0;
        int nbComm = 0;
        for (auto &mRef : mesuresRef)
        {
            for (auto &mAut : mesuresAutre)
            {
                if (mRef.getAttribut().attributId == mAut.getAttribut().attributId && mRef.getTimestamp() == mAut.getTimestamp())
                {
                    float err = mRef.getValeur() - mAut.getValeur();
                    somme2 += err * err;
                    ++nbComm;
                    break;
                }
            }
        }

        if (nbComm > 0)
        {
            float dist = sqrt(somme2 / nbComm);
            capteursSim.emplace_back(autre, dist);
        }
    }

    // 6) tri par distance croissante
    sort(capteursSim.begin(), capteursSim.end(),
         [](auto &a, auto &b)
         { return a.second < b.second; });

    return capteursSim;
}

void Application::ajouterCapteur(Capteur &capteur)
{
    /*
    Ajoute un capteur à la liste des capteurs de l'application.

    Arguments d'entrée :
    - capteur : référence au capteur à ajouter
    */

    listeTousLesCapteurs.push_back(capteur);
    return;
}

// On met ici les méthodes déclarées dans le .h
/*
float Application::estimerQualiteAir(float latitude, float longitude) const {}
void Application::ajouterPointUtilisateur(Utilisateur &user) const {}
void Application::analyserCapteurPrive() const {}
void Application::mesurerAlgorithme() const {}
void Application::faireMaintenance() {}
void Application::remplirCapteur() {}
Personne Application::authentifier(string identifiant, string mdp) {}*/