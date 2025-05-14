#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "Personne.h"
#include <string>

class Utilisateur : public Personne
{
private:
    long points;

public:
    Utilisateur(std::string id, std::string nom, long points);
    ~Utilisateur();

    void consulterPoints() const;
};

#endif