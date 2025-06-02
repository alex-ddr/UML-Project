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
    std::vector<Utilisateur> listeUtilisateurs;

public:
    // Constructeur
    Application() {}
    Application(const std::vector<Capteur> &listeTousLesCapteurs) : listeTousLesCapteurs(listeTousLesCapteurs) {}

    // Destructeur
    ~Application() {}

    // Méthodes implémentées 
    std::map<std::string, int> moyenneQualiteAir(float latitude, float longitude, time_t debut, time_t fin, float perimetre) ;
    std::vector<std::pair<Capteur, float>> listerCapteursSimilaires(Capteur &capteur, time_t debut, time_t fin) ;
    void ajouterPointUtilisateur(Utilisateur &user) const;
    void ajouterCapteur(Capteur &capteur);
    Capteur trouverCapteurParId(int id);
    bool chargerDonnees(const std::string &cheminFichierSensors, const std::string &cheminFichierUsers, const std::string &cheminFichierAttributs, const std::string &cheminFichierMesures);
    std::vector<Utilisateur> chargerUtilisateurs(const std::string& cheminFichierUsers);

    // Autres méthodes à implémenter dans le cadre de la complétude projet décrit (seulement 2 fonctionnalités sont demandées)
    // float estimerQualiteAirPointDonne(float latitude, float longitude) const;
    // void analyserCapteurPrive() const;
    // void faireMaintenance();
    // Personne authentifier(std::string identifiant, std::string mdp);

    // Getters
    std::vector<Capteur> getListeTousLesCapteurs() const { return listeTousLesCapteurs; }
    std::vector<Utilisateur> getListeUtilisateurs() const { return listeUtilisateurs; }

    // Setters
    void setListeTousLesCapteurs(const std::vector<Capteur> &listeTousLesCapteurs) { this->listeTousLesCapteurs = listeTousLesCapteurs; }
    void setListeUtilisateurs(const std::vector<Utilisateur> &listeUtilisateurs) { this->listeUtilisateurs = listeUtilisateurs; }
};