#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Parser.h"
#include "Mesure.h"
#include "Capteur.h"
#include "Attribut.h"
#include "Personne.h"
using namespace std;

time_t Parser::parseDate(string datetime_str)
{
    tm tm = {};
    istringstream ss(datetime_str);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (ss.fail())
    {
        cerr << "Parsing failed!" << endl;
        time_t return_failed = 0;
        return return_failed;
    }

    time_t timestamp = mktime(&tm);
    return timestamp;
}

vector<Capteur> Parser::chargerCapteurs(const string &cheminFichier)
{
    vector<Capteur> capteurs;
    ifstream fichier(cheminFichier);
    string ligne;

    if (!fichier.is_open())
    {
        cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << endl;
        return capteurs;
    }

    while (getline(fichier, ligne))
    {
        stringstream ss(ligne);
        string id, latStr, lonStr;

        getline(ss, id, ';');
        getline(ss, latStr, ';');
        getline(ss, lonStr, ';');

        if (!id.empty() && !latStr.empty() && !lonStr.empty())
        {
            double latitude = stod(latStr);
            double longitude = stod(lonStr);
            Capteur capteur(id, latitude, longitude);
            capteurs.push_back(capteur);
        }
    }

    fichier.close();
    return capteurs;
}

std::vector<Attribut> Parser::chargerAttributs(const std::string &cheminFichier)
{
    vector<Attribut> attributs;
    ifstream fichier(cheminFichier);
    string ligne;

    if (!fichier.is_open())
    {
        cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << endl;
        return;
    }

    while (getline(fichier, ligne))
    {
        stringstream ss(ligne);
        string id, unit, description;

        getline(ss, id, ';');
        getline(ss, unit, ';');
        getline(ss, description, ';');

        if (!id.empty() && !unit.empty() && !description.empty())
        {
            Attribut attribut{id, unit, description};
            attributs.push_back(attribut);
        }
    }

    fichier.close();
    return attributs;
}
/*
std::vector<Personne> Parser::chargerPersonnes(const std::string& cheminFichier) ; {
    vector<Attribut> attributs;
    ifstream fichier(cheminFichier);
    string ligne;

    if (!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichier << endl;
        return;
    }

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string id, unit, description;

        getline(ss, id, ';');
        getline(ss, unit, ';');
        getline(ss, description, ';');

    if (!id.empty() && !unit.empty() && !description.empty()) {
            Attribut attribut{id, unit, description};
            attributs.push_back(attribut);
        }
    }

    fichier.close();
    return attributs;
}


*/

void Parser::chargerMesures(const std::string &cheminFichierMesures, const std::string &cheminFichierAttributs, std::vector<Capteur> &capteurs)
{
    ifstream fichier(cheminFichierMesures);
    string ligne;
    vector<Attribut> listeAttributs = chargerAttributs(cheminFichierAttributs);

    if (!fichier.is_open())
    {
        cerr << "Erreur : impossible d'ouvrir le fichier " << cheminFichierMesures << endl;
        return;
    }

    while (getline(fichier, ligne))
    {
        stringstream ss(ligne);
        string timestamp, idCapteur, idAttribut, valeurStr;

        getline(ss, timestamp, ';');
        getline(ss, idCapteur, ';');
        getline(ss, idAttribut, ';');
        getline(ss, valeurStr, ';');

        if (!timestamp.empty() && !idCapteur.empty() && !idAttribut.empty() && !valeurStr.empty())
        {
            double valeur = stod(valeurStr);

            Attribut attribut;
            for (Attribut a : listeAttributs)
            {
                if (idAttribut == a.attributId)
                {
                    attribut = a;
                    break;
                }
            }

            Mesure mesure(parseDate(timestamp), valeur, attribut);

            for (Capteur &capteur : capteurs)
            {
                if (capteur.getCapteurId() == idCapteur)
                {
                    capteur.ajouterMesure(mesure);
                    break;
                }
            }
        }
    }

    fichier.close();
}
