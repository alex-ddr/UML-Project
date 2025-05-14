#include "Utilisateur.h"
#include <iostream>

Utilisateur::Utilisateur(std::string id, std::string nom, long points)
    : Personne(id, nom), points(points) {}

Utilisateur::~Utilisateur() {}

void Utilisateur::consulterPoints() const
{
    std::cout << "L'utilisateur a " << points << " points." << std::endl;
}