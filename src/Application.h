#include <iostream>
#include <cstring>


using namespace std;

class Application 
{
    public:
        float moyenneQualiteAir(float lat, float longitude, Date debut, Date fin,float perimetre) ;
        float estimerQualiteAir(float lat, float long);
        Capteur[] listerCapteursSimilaires(Capteur);
        void ajouterPointUtilisateur(Utilisateur user);
        void analyserCapteurPrive();
        void mesurerAlgorithme();
        void ajouterCapteur();
        void faireMaintenance();
        Personne authentifier(string identifiant, string mdp);

    private:
        Capteur* listeCapteurs;
        string identifiant;
}