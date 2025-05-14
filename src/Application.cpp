#include <iostream>
#include <cstring>
#include "Application.h"

using namespace std;

float Application::moyenneQualiteAir(float lat, float longitude, Date debut, Date fin, float perimetre) const
{
    if (listeCapteurs==NULL) {return -1;}
    
    int nbCapteurs = 0;
    int moyenneTotale =0;
    for (int i=0; )
}