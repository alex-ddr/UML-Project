#include <iostream>
#include <string>
#include "Application.h"
#include "Parser.h"

using namespace std;

// POUR CONVERTIR TIME_T : enlever 1970 années à l'année en question et convertir en secondes

void afficherMenuGouvernement()
{
    cout << "\nRôle : GOUVERNEMENT" << endl;
    cout << "*1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air à un point" << endl;
    cout << "*3. Lister les capteurs similaires" << endl;
    cout << "4. Analyser un capteur privé" << endl;
    cout << "5. Mesurer le temps d’exécution d’un algorithme" << endl;
    cout << "6. Quitter" << endl;
}

void afficherMenuUtilisateur()
{
    cout << "\nRôle : UTILISATEUR" << endl;
    cout << "*1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "*3. Lister les capteurs similaires" << endl;
    cout << "4. Consulter mes points" << endl;
    cout << "5. Quitter" << endl;
}

void afficherMenuAdmin()
{
    cout << "\nRôle : ADMIN" << endl;
    cout << "*1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "*3. Lister les capteurs similaires" << endl;
    cout << "4. Analyser un capteur privé" << endl;
    cout << "5. Mesurer le temps d’exécution d’un algorithme" << endl;
    cout << "6. Faire une maintenance" << endl;
    cout << "7. Quitter" << endl;
}

void demanderMoyenneQualiteAir(Application app)
{
    double latitude, longitude, rayon;
    string dateDebut, dateFin;

    cout << "Entrez la latitude : ";
    while (!(cin >> latitude) || latitude < -90.0 || latitude > 90.0)
    {
        cout << "Latitude invalide. Entrez une valeur entre -90 et 90 : ";
        cin.clear();
    }

    cout << "Entrez la longitude : ";
    while (!(cin >> longitude) || longitude < -180.0 || longitude > 180.0)
    {
        cout << "Longitude invalide. Entrez une valeur entre -180 et 180 : ";
        cin.clear();
    }

    cout << "Entrez le rayon (en km) : ";
    while (!(cin >> rayon) || rayon <= 0)
    {
        cout << "Rayon invalide. Entrez une valeur positive : ";
        cin.clear();
    }

    cout << "Entrez la date de début (YYYY-MM-DD HH:MM:SS) : ";
    cin.ignore();
    getline(cin, dateDebut);
    time_t debut = Parser::parseDate(dateDebut);
    while (debut <= 0)
    {
        cout << "Date de début invalide. Entrez une date au format YYYY-MM-DD HH:MM:SS : ";
        getline(cin, dateDebut);
        debut = Parser::parseDate(dateDebut);
    }

    cout << "Entrez la date de fin (YYYY-MM-DD HH:MM:SS) : ";
    getline(cin, dateFin);
    time_t fin = Parser::parseDate(dateFin);
    while (fin < debut)
    {
        cout << "Date de fin invalide. Elle doit être supérieure à la date de début : ";
        getline(cin, dateFin);
        fin = Parser::parseDate(dateFin);
    }

    cout << "  Moyenne qualité air :" << "\n";
    for (const auto &p : app.moyenneQualiteAir(latitude, longitude, debut, fin, rayon))
    {
        cout << "    " << p.first << " : " << p.second << "\n";
    }
}

void demanderListerCapteursSimilaires(Application app)
{
    int capteurId;
    cout << "Entrez l'identifiant du capteur (0 à 99) : ";
    while (!(cin >> capteurId) || capteurId < 0 || capteurId > 99)
    {
        cout << "Identifiant invalide. Entrez une valeur entre 0 et 99 : ";
        cin.clear();
    }

    cout << "Capteurs similaires au capteur " << capteurId << " :" << endl;
    Capteur capteur_choisi = app.trouverCapteurParId(capteurId);
    for (const auto &cap_mesure : app.listerCapteursSimilaires(capteur_choisi))
    {
        Capteur c = cap_mesure.first;
        float d = cap_mesure.second;

        cout << c << endl
             << "Distance : " << d << endl;
    }
}

int main()
{
    Application app = Application();
    if (!app.chargerDonnees("../data/sensors.csv", "../data/users.csv", "../data/attributes.csv", "../data/measurements.csv"))
        cout << "Erreur au chargement des données." << endl;
    string role;
    cout << "Veuillez entrer votre rôle :" << endl;
    cout << "- GOUVERNEMENT (g/G)" << endl;
    cout << "- UTILISATEUR (u/U)" << endl;
    cout << "- ADMIN (a/A)" << endl;
    cout << "> ";
    cin >> role;

    char choix = '0';
    bool quitter_programme = false;
    while (!quitter_programme)
    {
        if (role == "GOUVERNEMENT" || role == "g" || role == "G")
        {
            bool choix_valide = false;
            while (!choix_valide)
            {
                afficherMenuGouvernement();
                cout << "> ";
                cin >> choix;
                switch (choix)
                {
                case '1':
                    cout << "-> Moyenne dans une zone (GOUVERNEMENT)" << endl;
                    demanderMoyenneQualiteAir(app);
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation au point (GOUVERNEMENT)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Lister capteurs (GOUVERNEMENT)" << endl;
                    demanderListerCapteursSimilaires(app);
                    choix_valide = true;
                    break;
                case '4':
                    cout << "-> Analyse capteur privé (GOUVERNEMENT)" << endl;
                    choix_valide = true;
                    break;
                case '5':
                    cout << "-> Mesure de performance (GOUVERNEMENT)" << endl;
                    choix_valide = true;
                    break;
                case '6':
                    cout << "-> Fin du programme." << endl;
                    quitter_programme = true;
                    choix_valide = true;
                    break;
                default:
                    cout << "Choix invalide." << endl;
                    break;
                }
            }
        }
        else if (role == "UTILISATEUR" || role == "u" || role == "U")
        {
            bool choix_valide = false;
            while (!choix_valide)
            {
                afficherMenuUtilisateur();
                cout << "> ";
                cin >> choix;
                switch (choix)
                {
                case '1':
                    cout << "-> Moyenne dans une zone (UTILISATEUR)" << endl;
                    demanderMoyenneQualiteAir(app);
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation de qualité (UTILISATEUR)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Lister capteurs (UTILISATEUR)" << endl;
                    demanderListerCapteursSimilaires(app);
                    choix_valide = true;
                    break;
                case '4':
                    cout << "-> Consultation des points" << endl;
                    choix_valide = true;
                    break;
                case '5':
                    cout << "-> Fin du programme." << endl;
                    quitter_programme = true;
                    choix_valide = true;
                    break;
                default:
                    cout << "Choix invalide." << endl;
                    break;
                }
            }
        }
        else if (role == "ADMIN" || role == "a" || role == "A")
        {
            bool choix_valide = false;
            while (!choix_valide)
            {
                afficherMenuAdmin();
                cout << "> ";
                cin >> choix;
                switch (choix)
                {
                case '1':
                    cout << "-> Moyenne dans une zone (ADMIN)" << endl;
                    demanderMoyenneQualiteAir(app);
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation de qualité (ADMIN)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Lister capteurs (ADMIN)" << endl;
                    demanderListerCapteursSimilaires(app);
                    choix_valide = true;
                    break;
                case '4':
                    cout << "-> Analyse capteur privé (ADMIN)" << endl;
                    choix_valide = true;
                    break;
                case '5':
                    cout << "-> Mesure de performance (ADMIN)" << endl;
                    choix_valide = true;
                    break;
                case '6':
                    cout << "-> Maintenance (ADMIN)" << endl;
                    choix_valide = true;
                    break;
                case '7':
                    cout << "-> Fin du programme." << endl;
                    quitter_programme = true;
                    choix_valide = true;
                    break;
                default:
                    cout << "Choix invalide." << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Rôle inconnu." << endl;
            cout << "Veuillez entrer votre rôle :" << endl;
            cout << "- GOUVERNEMENT (g/G)" << endl;
            cout << "- UTILISATEUR (u/U)" << endl;
            cout << "- ADMIN (a/A)" << endl;
            cout << "> ";
            cin >> role;
        }
    }

    return 0;
}