#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
#include "Capteur.h"
using namespace std;

class Personne
{
protected:
    string id;
    string nom;
    Capteur liste_capteurs[];

public:
    Personne(string id, string nom);
    virtual ~Personne();
};

#endif