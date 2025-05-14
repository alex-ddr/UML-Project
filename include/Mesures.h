#ifndef MESURES_H
#define MESURES_H
using namespace std;

#include <ctime>
#include <Attribut.h>

class Mesures
{
private:
  time_t timestamp;
  float valeur;
  Attribut attribut;

public:
  // Constructors
  Mesures() : timestamp(0), valeur(0.0), attribut() {}
  Mesures(time_t timestamp, float valeur, Attribut attribut)
      : timestamp(timestamp), valeur(valeur), attribut(attribut) {}

  // Getters
  time_t getTimestamp() const { return timestamp; }
  float getValeur() const { return valeur; }
  Attribut getAttribut() const { return attribut; }

  // Setters
  void setTimestamp(time_t timestamp) { this->timestamp = timestamp; }
  void setValeur(float valeur) { this->valeur = valeur; }
  void setAttribut(Attribut attribut) { this->attribut = attribut; }

  // Destructor
  ~Mesures() {}
};
#endif