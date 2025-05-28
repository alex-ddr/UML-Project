#ifndef GOUVERNEMENT_H
#define GOUVERNEMENT_H

#include "Responsable.h"
#include <string>

class Gouvernement : public Responsable
{

    private:
        // Gouvernement est une classe héritière de Responsable 
        // Elle n'a pas d'attribut propre

        
    public:
        // Constructeurs
        Gouvernement(std::string identifiant, std::string mdp, const std::vector<Capteur>& listeCapteursPersonne = {}) 
            : Responsable(identifiant, mdp, listeCapteursPersonne) {}
        Gouvernement() : Responsable() {}

        // Destructeur
        ~Gouvernement() {}
};

#endif