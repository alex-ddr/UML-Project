#include "Application.h"
#include "Mesures.h"
#include <cmath>
#include <algorithm>

using namespace std;

float Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    if (listeCapteurs.empty())
        return -1;

    int nbCapteurs = 0;
    float moyenneTotale = 0;

    if (debut && fin)
    {
        for (const Capteur &c : listeCapteurs)
        {
            ++nbCapteurs;
            float moyenneCapteurs = 0;
            int nbMesures = 0;

            // for (const Mesures& m: c.getListeMesures())

            //     if(debut<m.getTimestamp & m.getTimestamp)
        }
    }
    return 0;
}

vector<pair<Capteur, float>> Application::listerCapteursSimilaires(Capteur &capteur) const
{
    // 1. Date la plus récente dans toutes les mesures
    vector<Mesures> liste_mesures_capteur = capteur.getListeMesures();
    time_t date_max = NULL;
    for (const Mesures &mesure : liste_mesures_capteur)
        if (!date_max || date_max < mesure.getTimestamp())
            date_max = mesure.getTimestamp();

    // 2. Date de début
    time_t date_debut = date_max - 7 * 24 * 60 * 60;

    // 3. Toutes les mesures de capteur entre date_debut et date_max
    vector<Mesures> liste_mesures;
    for (const auto &mesure : liste_mesures)
        if (mesure.getTimestamp() > date_debut)
            liste_mesures.push_back(mesure);

    // 4. Liste vide
    vector<pair<Capteur, float>> capteurs_similaires;

    // 5. Itération sur tous les capteurs
    for (const Capteur &capteur_autre : liste_capteurs)
    {
        // a)
        if (capteur_autre == capteur)
            continue;

        // b)
        vector<Mesures> liste_mesures_autres;
        for (const auto &mesure_autre : capteur_autre.getListeMesures())
            if (mesure_autre.getTimestamp() > date_debut)
                liste_mesures.push_back(mesure_autre);

        // c)
        float distance_totale = 0;
        // d)
        int nombre_commun = 0;

        // e)
        for (const auto &mesure : liste_mesures)
        {
            for (const auto &mesure_autre : liste_mesures_autres)
            {
                if (mesure.getAttribut().attribut_id == mesure_autre.getAttribut().attribut_id)
                {
                    float erreur = mesure.getValeur() - mesure_autre.getValeur();
                    distance_totale = distance_totale + erreur * erreur;
                    nombre_commun++;
                    break; // à vérifier
                }
            }
        }

        // f)
        float distance_moyenne = 0;
        if (nombre_commun > 0)
        {
            distance_moyenne = sqrt(distance_totale / nombre_commun);
            capteurs_similaires.push_back(make_pair(capteur_autre, distance_moyenne));
        }
    }

    // 6.
    sort(capteurs_similaires.begin(), capteurs_similaires.end(),
         [](const pair<Capteur, float> &a, const pair<Capteur, float> &b)
         {
             return a.second < b.second;
         });

    return capteurs_similaires;
}