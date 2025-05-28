#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include <iostream>
#include "Personne.h"

class Utilisateur : public Personne
{
    private:
        long points;

    public:
        // Constructeurs
        Utilisateur(std::string identifiant, std::string mdp, long points, const std::vector<Capteur>& listeCapteursPersonne = {})
        : Personne(identifiant, mdp, listeCapteursPersonne), points(points) {}
        Utilisateur() {}

        // Destructeur
        ~Utilisateur() {}

        // Getters
        long getPoints() const {return points;}

        // Setters
        void setPoints(const long& points) {this->points=points;}

        // Methodes
        void consulterPoints() const {std::cout << "L'utilisateur a " << points << " points." << std::endl;}
};

#endif