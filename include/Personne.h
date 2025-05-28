#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
#include <vector>
#include "Capteur.h"


class Personne
{
    protected:
        std::string identifiant;
        std::string mdp;
        std::vector<Capteur> listeCapteursPersonne;
        

    public:
        // Constructeurs
        Personne() {}
        Personne(const std::string &identifiant, const std::string &mdp, const std::vector<Capteur> &listeCapteursPersonne={}) 
            : identifiant(identifiant), mdp(mdp), listeCapteursPersonne(listeCapteursPersonne) {}

        // Destructeur
        virtual ~Personne() {}

        // Getters
        std::string getIdentifiant() const {return identifiant;}
        std::string getMdp() const {return mdp;}
        std::vector<Capteur> getListeCapteursPersonne() const {return listeCapteursPersonne;} 

        // Setters
        void setIdentifiant(const std::string &identifiant) {this->identifiant=identifiant;}
        void setMdp(const std::string &mdp) {this->mdp=mdp;}
        void setListeCapteursPersonne(const std::vector<Capteur> &listeCapteursPersonne) {this->listeCapteursPersonne=listeCapteursPersonne;}
};

#endif