#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
using namespace std;

class Personne
{
protected:
    string id;
    string nom;

public:
    Personne(string id, string nom);
    virtual ~Personne();
};

#endif