#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Capteur.h"
#include "Attribut.h"
#include "Personne.h"

class Parser
{
    private:

    public:
        static time_t parseDate(string datetime_str);
        std::vector<Capteur> chargerCapteurs(const std::string& cheminFichier) ;
        std::vector<Attribut> chargerAttributs(const std::string& cheminFichier) ;
        void chargerMesures(const std::string& cheminFichierMesures, const std::string& cheminFichierAttributs, std::vector<Capteur>& capteurs) ;
        std::vector<Personne> chargerPersonnes(const std::string& cheminFichier) ;
};

#endif