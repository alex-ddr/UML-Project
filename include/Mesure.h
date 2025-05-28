#ifndef MESURES_H
#define MESURES_H

#include <ctime>
#include "Attribut.h"

class Mesure
{
  private:
    time_t timestamp;
    float valeur;
    Attribut attribut;

  public:
    // Constructeurs
    Mesure() : timestamp(0), valeur(0.0), attribut() {}
    Mesure(time_t timestamp, float valeur, Attribut attribut)
        : timestamp(timestamp), valeur(valeur), attribut(attribut) {}

    // Destructeur
    ~Mesure() {}

    
    // Getters
    time_t getTimestamp() const { return timestamp; }
    float getValeur() const { return valeur; }
    Attribut getAttribut() const { return attribut; }

    // Setters
    void setTimestamp(time_t timestamp) { this->timestamp = timestamp; }
    void setValeur(float valeur) { this->valeur = valeur; }
    void setAttribut(Attribut attribut) { this->attribut = attribut; }

    // Surcharge de l'opérateur == 
    bool operator==(const Mesure &other) const
    {
      return (timestamp == other.timestamp &&
              valeur == other.valeur &&
              attribut == other.attribut);
    }
};
#endif