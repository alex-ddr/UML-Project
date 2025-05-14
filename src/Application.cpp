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

vector<Capteur> Application::listerCapteursSimilaires(Capteur &capteur) const
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
    vector<Capteur> capteurs_similaires;

    // 5. Itération sur tous les capteurs
    for (const Capteur &capteur_autre : liste_capteurs)
        return capteurs_similaires;
}