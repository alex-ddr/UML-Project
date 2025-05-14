#include <iostream>
#include <string>

using namespace std;

void afficherMenuGouvernement()
{
    cout << "\nRôle : GOUVERNEMENT" << endl;
    cout << "1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air à un point" << endl;
    cout << "3. Classifier les capteurs similaires" << endl;
    cout << "4. Analyser un capteur privé" << endl;
    cout << "5. Mesurer le temps d’exécution d’un algorithme" << endl;
    cout << "6. Quitter" << endl;
}

void afficherMenuUtilisateur()
{
    cout << "\nRôle : UTILISATEUR" << endl;
    cout << "1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "3. Classifier les capteurs similaires" << endl;
    cout << "4. Consulter mes points" << endl;
    cout << "5. Quitter" << endl;
}

void afficherMenuAdmin()
{
    cout << "\nRôle : ADMIN" << endl;
    cout << "1. Calculer la moyenne de qualité de l’air dans une zone" << endl;
    cout << "2. Estimer la qualité de l’air" << endl;
    cout << "3. Classifier les capteurs similaires" << endl;
    cout << "4. Analyser un capteur privé" << endl;
    cout << "5. Mesurer le temps d’exécution d’un algorithme" << endl;
    cout << "6. Faire une maintenance" << endl;
    cout << "7. Quitter" << endl;
}

int main()
{
    string role;
    cout << "Veuillez entrer votre rôle :" << endl;
    cout << "- GOUVERNEMENT" << endl;
    cout << "- UTILISATEUR" << endl;
    cout << "- ADMIN" << endl;
    cout << "> ";
    cin >> role;

    // Normalise le rôle (majuscule uniquement pour simplifier)
    for (auto &c : role)
        c = toupper(c);

    int choix = 0;
    do
    {
        if (role == "GOUVERNEMENT")
        {
            afficherMenuGouvernement();
            cout << "> ";
            cin >> choix;
            switch (choix)
            {
            case 1:
                cout << "-> Moyenne dans une zone (GOUVERNEMENT)" << endl;
                break;
            case 2:
                cout << "-> Estimation au point (GOUVERNEMENT)" << endl;
                break;
            case 3:
                cout << "-> Classification capteurs (GOUVERNEMENT)" << endl;
                break;
            case 4:
                cout << "-> Analyse capteur privé (GOUVERNEMENT)" << endl;
                break;
            case 5:
                cout << "-> Mesure de performance (GOUVERNEMENT)" << endl;
                break;
            case 6:
                cout << "-> Fin du programme." << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
                break;
            }
        }
        else if (role == "UTILISATEUR")
        {
            afficherMenuUtilisateur();
            cout << "> ";
            cin >> choix;
            switch (choix)
            {
            case 1:
                cout << "-> Moyenne dans une zone (UTILISATEUR)" << endl;
                break;
            case 2:
                cout << "-> Estimation de qualité (UTILISATEUR)" << endl;
                break;
            case 3:
                cout << "-> Classification capteurs (UTILISATEUR)" << endl;
                break;
            case 4:
                cout << "-> Consultation des points" << endl;
                break;
            case 5:
                cout << "-> Fin du programme." << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
                break;
            }
        }
        else if (role == "ADMIN")
        {
            afficherMenuAdmin();
            cout << "> ";
            cin >> choix;
            switch (choix)
            {
            case 1:
                cout << "-> Moyenne dans une zone (ADMIN)" << endl;
                break;
            case 2:
                cout << "-> Estimation de qualité (ADMIN)" << endl;
                break;
            case 3:
                cout << "-> Classification capteurs (ADMIN)" << endl;
                break;
            case 4:
                cout << "-> Analyse capteur privé (ADMIN)" << endl;
                break;
            case 5:
                cout << "-> Mesure de performance (ADMIN)" << endl;
                break;
            case 6:
                cout << "-> Maintenance (ADMIN)" << endl;
                break;
            case 7:
                cout << "-> Fin du programme." << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
                break;
            }
        }
        else
        {
            cout << "Rôle inconnu. Veuillez relancer le programme." << endl;
            break;
        }

    } while ((role == "GOUVERNEMENT" && choix != 6) ||
             (role == "UTILISATEUR" && choix != 5) ||
             (role == "ADMIN" && choix != 7));

    return 0;
}