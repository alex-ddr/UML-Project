#include <iostream>
#include <cstring>
#include <ctime>
#include "Capteur.h"
#include "Utilisateur.h"

using namespace std;

class Application
{
public:
    float moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const;
    float estimerQualiteAir(float latitude, float longitude) const;
    Capteur *listerCapteursSimilaires(Capteur &capteur) const;
    void ajouterPointUtilisateur(Utilisateur &user) const;
    void analyserCapteurPrive() const;
    void mesurerAlgorithme() const;
    void ajouterCapteur();
    void faireMaintenance();
    Personne authentifier(string identifiant, string mdp);

private:
    Capteur *listeCapteurs;
    string identifiant;
};