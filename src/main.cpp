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
    cout << "*3. Classer les capteurs par similarité par rapport à un capteur de référence" << endl;
    cout << "4. Analyser un capteur privé" << endl;
    cout << "5. Mesurer le temps d’exécution d’un algorithme" << endl;
    cout << "6. Quitter" << endl;
}

void afficherMenuUtilisateur()
{
    cout << "\nRôle : UTILISATEUR" << endl;
    cout << "*1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "*3. Classer les capteurs par similarité par rapport à un capteur de référence" << endl;
    cout << "4. Consulter mes points" << endl;
    cout << "5. Quitter" << endl;
}

void afficherMenuAdmin()
{
    cout << "\nRôle : ADMIN" << endl;
    cout << "*1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "*3. Classer les capteurs par similarité par rapport à un capteur de référence" << endl;
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

    string reponse_date_fin;
    cout << endl;
    cout << "La date de fin est facultative. " << endl;
    cout << "Par défaut, date_fin = date_début + 24H " << endl;
    cout << "Voulez vous entrer une date de fin ? (o/n)" << endl;
    cout << "> ";
    cin >> reponse_date_fin;
    cin.ignore();

    while (reponse_date_fin != "o" && reponse_date_fin != "n")
    {
        cout << "Réponse invalide. Entrez 'o' si oui, 'n' sinon : ";
        getline(cin, reponse_date_fin);
    }

    time_t fin = -1;
    if (reponse_date_fin == "o")
    {
        cout << "Entrez la date de fin (YYYY-MM-DD HH:MM:SS) : ";
        getline(cin, dateFin);
        fin = Parser::parseDate(dateFin);
        while (fin < debut)
        {
            cout << "Date de fin invalide. Elle doit être supérieure à la date de début : ";
            getline(cin, dateFin);
            fin = Parser::parseDate(dateFin);
        }
    }

    map<string, int> res = app.moyenneQualiteAir(latitude, longitude, debut, fin, rayon);
    if (not res.empty())
    {
        cout << "  Moyenne qualité air :" << "\n";
        for (const auto &p : res)
        {
            cout << "    " << p.first << " : " << p.second << "\n";
        }
    }

    else
        cout << "Aucun capteur trouvé dans ce périmètre et pour cette période. " << endl;

    cout << "\n----------------------------------------\n\n";
}

void demanderListerCapteursSimilaires(Application app)
{
    // Demander l'identifiant du capteur
    int capteurId;
    cout << "Entrez l'identifiant du capteur (0 à 99) : ";
    while (!(cin >> capteurId) || capteurId < 0 || capteurId > 99)
    {
        cout << "Identifiant invalide. Entrez une valeur entre 0 et 99 : ";
        cin.clear();
    }

    // Demander la date de début
    string dateDebut, dateFin;
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

    // Demander la date de fin
    cout << "Entrez la date de fin (YYYY-MM-DD HH:MM:SS) : ";
    getline(cin, dateFin);
    time_t fin = Parser::parseDate(dateFin);
    while (fin < debut)
    {
        cout << "Date de fin invalide. Elle doit être supérieure à la date de début : ";
        getline(cin, dateFin);
        fin = Parser::parseDate(dateFin);
    }

    // Afficher les capteurs par ordre de similarité
    cout << "Classement des capteurs par similarité par rapport au capteur de référence " << capteurId << " :" << endl;
    Capteur capteur_ref = app.trouverCapteurParId(capteurId);
    for (const auto &capteur_mesure : app.listerCapteursSimilaires(capteur_ref, debut, fin))
    {
        Capteur c = capteur_mesure.first;
        float d = capteur_mesure.second;

        cout << endl;
        cout << "Capteur : " << c.getCapteurId() << endl;
        cout << "Ecrat-type (plus il est petit, plus le capteur est similaire) : " << d << endl;
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