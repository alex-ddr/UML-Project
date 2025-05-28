#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <string>
#include <iostream>

// Attribut n'est pas une Classe mais un Struct.
// La seule chose qui change, c'est que les membres sont publics par défaut
// Sinon même fonctionnement que pour une Classe.

struct Attribut
{
  std::string attributId;
  std::string unit;
  std::string description;

  bool operator==(const Attribut &other) const
  {
    return attributId == other.attributId &&
           unit == other.unit &&
           description == other.description;
  }

  friend std::ostream &operator<<(std::ostream &os, const Attribut &attr)
  {
    os << "AttributId: " << attr.attributId
       << ", Unit: " << attr.unit
       << ", Description: " << attr.description;
    return os;
  }
};

#endif