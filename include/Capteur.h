#ifndef CAPTEUR_H
#define CAPTEUR_H
using namespace std;

#include <string>
#include "Mesures.h"
class Capteur
{
private:
  long capteur_id;
  float latitude;
  float longitude;
  bool confiance;
  bool prive;
  Mesures liste_mesures[];

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

  // Setters
  void setCapteurId(long id) { capteur_id = id; }
  void setLatitude(float lat) { latitude = lat; }
  void setLongitude(float lon) { longitude = lon; }
  void setConfiance(bool conf) { confiance = conf; }
  void setPrive(bool priv) { prive = priv; }

  // Destructor
  ~Capteur() {}
};
#endif