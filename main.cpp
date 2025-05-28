#include <iostream>
#include <string>

using namespace std;

// POUR CONVERTIR TIME_T : enlever 1970 années à l'année en question et convertir en secondes

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
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation au point (GOUVERNEMENT)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Classification capteurs (GOUVERNEMENT)" << endl;
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
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation de qualité (UTILISATEUR)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Classification capteurs (UTILISATEUR)" << endl;
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
                    choix_valide = true;
                    break;
                case '2':
                    cout << "-> Estimation de qualité (ADMIN)" << endl;
                    choix_valide = true;
                    break;
                case '3':
                    cout << "-> Classification capteurs (ADMIN)" << endl;
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