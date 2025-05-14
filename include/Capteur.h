#ifndef CAPTEUR_H
#define CAPTEUR_H
using namespace std;

#include <string>
#include "Mesures.h"
#include <vector>
class Capteur
{
private:
  long capteur_id;
  float latitude;
  float longitude;
  bool confiance;
  bool prive;
  vector<Mesures> liste_mesures;

public:
  // Constructor
  Capteur(long id, float lat, float lon, bool conf, bool priv)
      : capteur_id(id), latitude(lat), longitude(lon), confiance(conf), prive(priv)
  {
  }

  // Méthodes
  bool estCapteurDeConfiance();

  // Getters
  long getCapteurId() const { return capteur_id; }
  float getLatitude() const { return latitude; }
  float getLongitude() const { return longitude; }
  bool isConfiance() const { return confiance; }
  bool isPrive() const { return prive; }
  vector<Mesures> getListeMesures() const { return liste_mesures; }

  // Setters
  void setCapteurId(long id) { capteur_id = id; }
  void setLatitude(float lat) { latitude = lat; }
  void setLongitude(float lon) { longitude = lon; }
  void setConfiance(bool conf) { confiance = conf; }
  void setPrive(bool priv) { prive = priv; }

  bool operator==(const Capteur &other) const
  {
    return capteur_id == other.capteur_id &&
           latitude == other.latitude &&
           longitude == other.longitude &&
           confiance == other.confiance &&
           prive == other.prive &&
           liste_mesures == other.liste_mesures;
  }

  // Destructor
  ~Capteur() {}
};
#endif