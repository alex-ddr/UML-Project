#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <string>
#include <vector>
#include "Mesure.h"

class Capteur
{
  private:
    long capteurId;
    float latitude;
    float longitude;
    bool confiance;
    bool prive;
    std::vector<Mesure> listeMesures;

  public:
    // Constructeur
    Capteur(long id, float lat, float lon, bool conf, bool priv, std::vector<Mesure> listeMesures)
        : capteurId(id), latitude(lat), longitude(lon), confiance(conf), prive(priv), listeMesures(listeMesures)
    {}

    // Méthodes
    bool estCapteurDeConfiance();

    // Getters
    long getCapteurId() const { return capteurId; }
    float getLatitude() const { return latitude; }
    float getLongitude() const { return longitude; }
    bool isConfiance() const { return confiance; }
    bool isPrive() const { return prive; }
    std::vector<Mesure> getListeMesures() const { return listeMesures; }

    // Setters
    void setCapteurId(long id) { capteurId = id; }
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

    // Destructeur
    ~Capteur() {}
};
#endif