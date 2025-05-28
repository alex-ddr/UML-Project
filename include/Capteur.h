#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <string>
#include <vector>
#include "Mesure.h"

class Capteur
{
private:
  std::string capteurId;
  float latitude;
  float longitude;
  bool confiance;
  bool prive;
  std::vector<Mesure> listeMesures;

public:
  // Constructeur
  Capteur(const std::string &id,
          float lat,
          float lon,
          bool conf = true,
          bool priv = false,
          std::vector<Mesure> lm = {})
      : capteurId(id), latitude(lat), longitude(lon), confiance(conf), prive(priv), listeMesures(std::move(lm))
  {
  }

  // Méthodes
  bool estCapteurDeConfiance();
  void ajouterMesure(const Mesure &mesure) { listeMesures.push_back(mesure); }

  // Getters
  const std::string &getCapteurId() const { return capteurId; }
  float getLatitude() const { return latitude; }
  float getLongitude() const { return longitude; }
  bool isConfiance() const { return confiance; }
  bool isPrive() const { return prive; }
  const std::vector<Mesure> &getListeMesures() const { return listeMesures; }

  // Setters
  void setCapteurId(const std::string &id) { capteurId = id; }
  void setLatitude(float lat) { latitude = lat; }
  void setLongitude(float lon) { longitude = lon; }
  void setConfiance(bool conf) { confiance = conf; }
  void setPrive(bool priv) { prive = priv; }

  bool operator==(const Capteur &other) const
  {
    return capteurId == other.capteurId &&
           latitude == other.latitude &&
           longitude == other.longitude &&
           confiance == other.confiance &&
           prive == other.prive &&
           listeMesures == other.listeMesures;
  }

  friend std::ostream &operator<<(std::ostream &os, const Capteur &capteur)
  {
    os << "Capteur[ID: " << capteur.capteurId
       << ", Latitude: " << capteur.latitude
       << ", Longitude: " << capteur.longitude
       << ", Confiance: " << (capteur.confiance ? "true" : "false")
       << ", Prive: " << (capteur.prive ? "true" : "false")
       << ", Mesures: [";
    for (size_t i = 0; i < capteur.listeMesures.size(); ++i)
    {
      os << capteur.listeMesures[i];
      if (i != capteur.listeMesures.size() - 1)
        os << ", ";
    }
    os << "]]";
    return os;
  }

  // Destructeur
  ~Capteur() {}
};

#endif // CAPTEUR_H