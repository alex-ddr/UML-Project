#ifndef RESPONSABLE_H
#define RESPONSABLE_H

#include "Personne.h"
#include <string>

class Responsable : public Personne
{
public:
    Responsable(std::string id, std::string nom);
    ~Responsable();
};

#endif