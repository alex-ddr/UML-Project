#include "Application.h"
#include "Mesures.h"
#include <vector>

using namespace std;

float Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    if (listeCapteurs.empty())
        return -1;

    int nbCapteurs = 0;
    float moyenneTotale = 0;

    if (debut && fin)
    {
        for (const int i=0; i<taille; ++i)
        {
            ++nbCapteurs;
            float moyenneCapteurs=0;
            int nbMesures=0;



        }
    }
    return 0;
}

Capteur *Application::listerCapteursSimilaires(Capteur &capteur) const
{
    // 1. Date la plus récente dans toutes les mesures
    vector<Mesures> liste_mesures_capteur = capteur.getListeMesures();
    time_t date_max = NULL;
    for (const auto &mesure : liste_mesures_capteur)
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
    vector<Capteur> capteurs_similaires;
}