#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "Responsable.h"


class Admin : public Responsable
{
    private:
        // Responsable est une classe héritière de Personne 
        // Elle n'a pas d'attribut propre

        
    public:
        // Constructeurs 
        Admin(std::string identifiant, std::string mdp, const std::vector<Capteur>& listeCapteursPersonne = {}) 
            : Responsable(identifiant, mdp, listeCapteursPersonne) {}

        // Destructeur
        ~Admin() {}
};

#endif
