#include "Application.h"
#include "Mesures.h"
#include <cmath>
#include <algorithm>

using namespace std;

map<string, float> Application::moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const
{
    map<string, float> moyennesParGaz={
        {"O3", 0.0},
        {"SO2", 0.0},
        {"NO2", 0.0},
        {"PM10", 0.0}
    };

    string gaz[4]= {"O3", "SO2", "NO2", "PM10"};
    int nbCapteurs[4] ={0};
    float moyennesTotales[4] ={0};


    if (!fin) {fin=debut+24*3600;} // si pas de fin définie, alors par défaut la fin est le jour de début + 1
    
    for (const Capteur& c: liste_capteurs)
    {
        
        float moyennes[4] ={0};
        int nbMesures[4]={0};
        
        for (const Mesures& m: c.getListeMesures()){
            

            if(debut<m.getTimestamp() && m.getTimestamp() <fin)
            {
                if ( m.getAttribut().attribut_id == "O3")
                {
                    moyennes[0] += m.getValeur();
                    ++nbMesures[0];
                    ++nbCapteurs[0];
                }
                else if ( m.getAttribut().attribut_id == "SO2")
                {
                    moyennes[1]+= m.getValeur();
                    ++nbMesures[1];
                    ++nbCapteurs[1];
                }
                else if ( m.getAttribut().attribut_id == "NO2")
                {
                    moyennes[2]+= m.getValeur();
                    ++nbMesures[2];
                    ++nbCapteurs[2];
                }
                else if ( m.getAttribut().attribut_id == "PM10")
                {
                    moyennes[3]+= m.getValeur();
                    ++nbMesures[3];
                    ++nbCapteurs[3];
                }
            }

            for (int i =0; i<4; ++i){
                if (nbMesures[i] > 0) {
                moyennes[i] /= nbMesures[i];
                moyennesTotales[i] += moyennes[i];
                }
            }
        }
    }

    for (int i =0; i<4; ++i){
        if (nbCapteurs[i]>0) moyennesTotales[i]/=nbCapteurs[i];
        moyennesParGaz[gaz[i]] = moyennesTotales[i];
    }
    return moyennesParGaz;
}

vector<pair<Capteur, float>> Application::listerCapteursSimilaires(Capteur &capteur) const
{
    // 1. Date la plus récente dans toutes les mesures
    vector<Mesures> liste_mesures_capteur = capteur.getListeMesures();
    time_t date_max = 0;
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

void Application::ajouterCapteur()
{
    // Lit le csv Sensor.csv
    // Crée un capteur
    // Ajoute le capteur à la liste de capteurs

    return;
}