#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "include/Application.h"

using namespace std;

int main()
{

  // test méthode moyenneQualiteAir de la classe application
  float lat;
  float longitude;
  int perimetre;
  time_t debut;
  time_t fin;
  map<string, float> qualiteAirParGaz;

  cout << "Veuillez entrer une latitude :" << endl;
  cin >> lat;
  cout << "Veuillez entrer une longitude :" << endl;
  cin >> longitude;
  cout << "Veuillez entrer un périmètre :" << endl;
  cin >> perimetre;
  cout << "Veuillez entrer une date de début (timestamp) :" << endl;
  cin >> debut;
  cout << "Veuillez entrer une date de fin (timestamp) :" << endl;
  cin >> fin;

  Application app;
  qualiteAirParGaz = app.moyenneQualiteAir(lat, longitude, debut, fin, perimetre);

  for (auto it = qualiteAirParGaz.begin(); it != qualiteAirParGaz.end(); ++it)
  {
      cout << "Gaz : " << it->first << ", valeur : " << it->second << endl;
  }

  return 0;
}