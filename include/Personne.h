#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
#include "Capteur.h"
#include <vector>
using namespace std;

class Personne
{
protected:
    string id;
    string nom;
    vector<Capteur> liste_capteurs;

public:
    // Constructors
    Personne() {};
    Personne(const string &id, const string &nom, const vector<Capteur> &liste_capteurs)
        : id(id), nom(nom), liste_capteurs(liste_capteurs) {}

    // Destructor
    virtual ~Personne() {};

    // Getters
    string getId() const { return id; }
    string getNom() const { return nom; }
    vector<Capteur> getListeCapteurs() const { return liste_capteurs; }

    // Setters
    void setId(const string &id) { this->id = id; }
    void setNom(const string &nom) { this->nom = nom; }
    void setListeCapteurs(const vector<Capteur> &liste_capteurs) { this->liste_capteurs = liste_capteurs; }
};

#endif