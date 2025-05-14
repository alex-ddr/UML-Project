#include "Application.h"
#include "Mesures.h"

using namespace std;

float Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    if (listeCapteurs == NULL)
        return -1;

    int nbCapteurs = 0;
    int moyenneTotale = 0;
    return 0;
}

Capteur *Application::listerCapteursSimilaires(Capteur &capteur) const
{
    Mesures *liste_mesures_capteur = capteur
}