#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "Application.h"
#include "Capteur.h"

using namespace std;

template <typename Func, typename... Args>
double mesurerTempsExecution(Func func, Args &&...args)
{
  clock_t start = clock();
  func(std::forward<Args>(args)...);
  clock_t end = clock();
  return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int main()
{
  // Test listerCapteursSimilaires
  Application app;
  // Exemple de capteur
}
