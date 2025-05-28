#include <string>
#include <ctime>
#include <vector>
#include <utility>
#include <map>
#include "Capteur.h"
#include "Utilisateur.h"

class Application
{
private:
    std::vector<Capteur> listeTousLesCapteurs;

public:
    // Constructeur
    Application() {}
    Application(const std::vector<Capteur> &listeTousLesCapteurs) : listeTousLesCapteurs(listeTousLesCapteurs) {}

    // Destructeur
    ~Application() {}

    // Méthodes
    std::map<std::string, float> moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) const;
    float estimerQualiteAir(float latitude, float longitude) const;
    std::vector<std::pair<Capteur, float>> listerCapteursSimilaires(Capteur &capteur) const;
    void ajouterPointUtilisateur(Utilisateur &user) const;
    void analyserCapteurPrive() const;
    void mesurerAlgorithme() const;
    void ajouterCapteur(Capteur &capteur);
    void faireMaintenance();
    void remplirCapteur();
    Personne authentifier(std::string identifiant, std::string mdp);

    // Getters
    std::vector<Capteur> getListeTousLesCapteurs() const { return listeTousLesCapteurs; }

    // Setters
    void setListeTousLesCapteurs(const std::vector<Capteur> &listeTousLesCapteurs) { this->listeTousLesCapteurs = listeTousLesCapteurs; }
};