#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include "Capteur.h"
#include "Utilisateur.h"

using namespace std;

class Application
{
private:
    vector<Capteur> liste_capteurs;

public:
    // Constructeur
    Application() {}
    Application(const vector<Capteur> &liste_capteurs)
        : liste_capteurs(liste_capteurs) {}

    // Déstructeur
    ~Application() {}

    // Méthodes
    float moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const;
    float estimerQualiteAir(float latitude, float longitude) const;
    vector<Capteur> listerCapteursSimilaires(Capteur &capteur) const;
    void ajouterPointUtilisateur(Utilisateur &user) const;
    void analyserCapteurPrive() const;
    void mesurerAlgorithme() const;
    void ajouterCapteur();
    void faireMaintenance();
    Personne authentifier(string identifiant, string mdp);

    // Getters
    vector<Capteur> getListeCapteurs() const { return liste_capteurs; }

    // Setters
    void setListeCapteurs(const vector<Capteur> &liste_capteurs) { this->liste_capteurs = liste_capteurs; }
};