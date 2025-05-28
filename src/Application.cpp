#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <map>
#include <algorithm>
#include <cmath>
#include "Application.h"
#include "Mesure.h"
using namespace std;

// fonction pour calculer la distance euclidienne entre deux points
float distance(float lat1, float lon1, float lat2, float lon2)
{
    return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

map<string, float> Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
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
    - std::map<std::string, float> : moyennes des concentrations mesurées pour chaque gaz ("O3", "SO2", "NO2", "PM10")
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
    return moyennesParGaz;
}

vector<pair<Capteur, float>> Application::listerCapteursSimilaires(Capteur &capteur) const
{
    /*
    Retourne une liste des capteurs similaires à un capteur donné, avec une mesure de la distance d'erreur moyenne.

    Arguments d'entrée :
    - capteur : référence au capteur de référence pour la comparaison

    Fonctionnement :
    - Calcule la date la plus récente parmi les mesures du capteur donné.
    - Définit une période d'une semaine avant cette date.
    - Pour chaque capteur dans la liste globale, calcule la distance moyenne quadratique
       des valeurs mesurées communes dans cette période.
    - Trie les capteurs par similarité croissante (distance moyenne la plus faible en premier).

    Retour :
    - std::vector<std::pair<Capteur, float>> : vecteur de paires (capteur, distance moyenne d'erreur)
    */

    // 1. Date la plus récente dans toutes les mesures
    vector<Mesure> listeMesuresCapteur = capteur.getListeMesures();
    time_t dateMax = 0;
    for (const Mesure &mesure : listeMesuresCapteur)
        if (!dateMax || dateMax < mesure.getTimestamp())
            dateMax = mesure.getTimestamp();

    // 2. Date de début
    time_t dateDebut = dateMax - 7 * 24 * 60 * 60;

    // 3. Toutes les mesures de capteur entre date_debut et date_max
    vector<Mesure> listeMesures;
    for (const auto &mesure : listeMesures)
        if (mesure.getTimestamp() > dateDebut)
            listeMesures.push_back(mesure);

    // 4. Liste vide
    vector<pair<Capteur, float>> capteursSimilaires;

    // 5. Itération sur tous les capteurs
    for (const Capteur &capteurAutre : listeTousLesCapteurs)
    {
        // a)
        if (capteurAutre == capteur)
            continue;

        // b)
        vector<Mesure> listeMesuresAutres;
        for (const auto &mesureAutre : capteurAutre.getListeMesures())
            if (mesureAutre.getTimestamp() > dateDebut)
                listeMesures.push_back(mesureAutre);

        // c)
        float distanceTotale = 0;
        // d)
        int nombreCommun = 0;

        // e)
        for (const auto &mesure : listeMesures)
        {
            for (const auto &mesureAutre : listeMesuresAutres)
            {
                if (mesure.getAttribut().attributId == mesureAutre.getAttribut().attributId)
                {
                    float erreur = mesure.getValeur() - mesureAutre.getValeur();
                    distanceTotale = distanceTotale + erreur * erreur;
                    nombreCommun++;
                    break; // à vérifier
                }
            }
        }

        // f)
        float distanceMoyenne = 0;
        if (nombreCommun > 0)
        {
            distanceMoyenne = sqrt(distanceTotale / nombreCommun);
            capteursSimilaires.push_back(make_pair(capteurAutre, distanceMoyenne));
        }
    }

    // 6.
    sort(capteursSimilaires.begin(), capteursSimilaires.end(),
         [](const pair<Capteur, float> &a, const pair<Capteur, float> &b)
         {
             return a.second < b.second;
         });

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