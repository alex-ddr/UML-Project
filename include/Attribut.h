#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <string>
using namespace std;

struct Attribut
{
  string attribut_id;
  string unit;
  string description;

  bool operator==(const Attribut &other) const
  {
    return attribut_id == other.attribut_id &&
           unit == other.unit &&
           description == other.description;
  }
};

#endif // ATTRIBUT_H