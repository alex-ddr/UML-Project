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
    Mesures *liste_mesures_capteur = capteur
}