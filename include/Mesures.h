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
  Mesures();
  Mesures(time_t timestamp, float valeur, Attribut attribut);

  // Getters
  time_t getTimestamp() const;
  float getValeur() const;
  Attribut getAttribut() const;

  // Setters
  void setTimestamp(time_t timestamp);
  void setValeur(float valeur);
  void setAttribut(Attribut attribut);

  // Destructor
  ~Mesures();
};
#endif