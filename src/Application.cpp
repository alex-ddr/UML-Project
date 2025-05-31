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

bool Application::chargerDonnees(const std::string &cheminFichierSensors, const string &cheminFichierUsers, const std::string &cheminFichierAttributs, const string &cheminFichierMesures)
{

    listeTousLesCapteurs = Parser::chargerCapteurs(cheminFichierSensors, cheminFichierUsers);
    Parser ::chargerMesures(cheminFichierMesures, cheminFichierAttributs, listeTousLesCapteurs);

    if (listeTousLesCapteurs.empty())
        return false;
    return true;
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

Capteur Application::trouverCapteurParId(int id)
{
    for (const auto &cap : listeTousLesCapteurs)
        if (cap.getCapteurId() == ("Sensor" + to_string(id)))
            return cap;
    Capteur return_cap = Capteur("Sensor1000", 0.0f, 0.0f, true, false, {});
    return return_cap;
}

map<string, int> Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    /*
    Calcule la moyenne de la qualité de l'air pour différents gaz sur une période donnée et dans une zone géographique.

    Arguments d'entrée :
    - latitude : latitude du centre de la zone d'étude (float)
    - longitude : longitude du centre de la zone d'étude (float)
    - debut : timestamp de début de la période (time_t)
    - fin : timestamp de fin de la période (time_t). Si = -1, la période est d'une journée à partir de debut.
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

    if (fin <= 0)
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

        // Pour chaque mesure du capteur,
        // qui est bien incluse dans l'intervalle de temps souhaité,
        // on regarde à quel gaz elle correspond parmi O3, SO2, NO2 et PM10
        // et pour ce gaz là, on incrémente le nombre de mesures
        // et on ajoute la mesure à sa moyenne
        for (const Mesure &m : c.getListeMesures())
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
    bool capteurs_touves = false;
    // Enfin, la moyenne finale par gaz (moyenne des moyennes de tous les capteurs)
    for (int i = 0; i < 4; ++i)
    {
        if (nbCapteurs[i] > 0)
        {
            moyennesTotales[i] /= nbCapteurs[i];
            capteurs_touves = true;
        }
        moyennesParGaz[gaz[i]] = moyennesTotales[i];
        // cout << "moyennesParGaz pour gaz " << i << " " << moyennesTotales[i] << endl;
    }

    if (capteurs_touves == false)
    {
        return map<string, int>();
    }

    return calculerIndicesATMO(moyennesParGaz);
}

vector<pair<Capteur, float>> Application::listerCapteursSimilaires(Capteur &capteur, time_t debut, time_t fin) const
{
    // filtrage des mesures du capteur de référence entre debut et fin
    vector<Mesure> mesuresCapteurRef = capteur.getListeMesures();
    vector<Mesure> mesuresCapteurRefDansIntervalleTemps;
    for (Mesure &m : mesuresCapteurRef)
        if (m.getTimestamp() >= debut && m.getTimestamp() <= fin)
            mesuresCapteurRefDansIntervalleTemps.push_back(m);

    vector<pair<Capteur, float>> capteursSimilaires;
    for (Capteur autre : listeTousLesCapteurs)
    {
        // on ne prend pas le capteur de référence
        if (autre == capteur)
            continue;
        // si on gère la fiabilité RAJOUTER UN TRUC
        if (!autre.isConfiance())
            continue; // on ne prend pas les capteurs non fiables

        // on ajoute à la liste mesuresAutre les données des autres capteurs, comprises entre debut et fin
        vector<Mesure> mesuresAutre;
        for (Mesure m : autre.getListeMesures())
            if (m.getTimestamp() >= debut && m.getTimestamp() <= fin)
                mesuresAutre.push_back(m);

        // calcul de la somme des écarts-type entre les valeurs du capteur de référence et d'un autre capteur
        float sommeDesEcartsType = 0;
        int nbValeurs = 0;
        for (Mesure &mRef : mesuresCapteurRefDansIntervalleTemps)
        {
            for (Mesure &mAut : mesuresAutre)
            {
                // on fait correspondre les gaz et les temps associés au mesures
                if (mRef.getAttribut().attributId == mAut.getAttribut().attributId && mRef.getTimestamp() == mAut.getTimestamp())
                {
                    float err = mRef.getValeur() - mAut.getValeur();
                    sommeDesEcartsType += err * err;
                    ++nbValeurs;
                    break;
                }
            }
        }

        // calcul de la variance (racine de l'écart-type),
        // et ajout de cet autre capteur dans la liste des capteurs similaires
        if (nbValeurs > 0)
        {
            float variance = sqrt(sommeDesEcartsType / nbValeurs);
            capteursSimilaires.emplace_back(autre, variance);
        }
    }

    // tri par variance croissante
    sort(capteursSimilaires.begin(), capteursSimilaires.end(),
         [](pair<Capteur, float> &capteurA, pair<Capteur, float> &capteurB)
         { return capteurA.second < capteurB.second; });

    return capteursSimilaires;
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