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
    static time_t parseDate(std::string datetime_str);
    static std::vector<Capteur> chargerCapteurs(const std::string &cheminFichierSensors, const std::string &cheminFichierUsers);
    static std::vector<Attribut> chargerAttributs(const std::string &cheminFichier);
    static void chargerMesures(const std::string &cheminFichierMesures, const std::string &cheminFichierAttributs, std::vector<Capteur> &capteurs);
    static std::vector<std::string> chargerCapteursPrive(const std::string& cheminFichier) ;


};

#endif