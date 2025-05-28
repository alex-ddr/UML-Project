#ifndef RESPONSABLE_H
#define RESPONSABLE_H

#include "Personne.h"
#include <string>
#include <vector>

class Responsable : public Personne
{
    private:
        // Responsable est une classe héritière de Personne 
        // Elle n'a pas d'attribut propre


    public:
        // Constructeurs
        Responsable(const std::string& identifiant, const std::string& mdp, const std::vector<Capteur>& listeCapteursPersonne = {})
            : Personne(identifiant, mdp, listeCapteursPersonne) {}

        Responsable() : Personne() {}

        // Destructeur
        ~Responsable() {}
};

#endif
