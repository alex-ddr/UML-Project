#ifndef GOUVERNEMENT_H
#define GOUVERNEMENT_H

#include "Responsable.h"
#include <string>

class Gouvernement : public Responsable
{
public:
    Gouvernement(std::string id, std::string nom);
    ~Gouvernement();
};

#endif