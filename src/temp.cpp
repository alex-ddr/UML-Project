#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "Application.h"
#include <sstream>
#include <iomanip>

using namespace std;

template <typename Func, typename... Args>
void mesurerTempsExecution(Func func, Args &&...args)
{
  clock_t start = clock();
  func(forward<Args>(args)...);
  clock_t end = clock();
  double elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  cout << "------------------------------------------" << endl;
  cout << "| Temps d'execution : " << fixed << setprecision(6) << elapsed << " secondes" << endl;
  cout << "------------------------------------------" << endl;
}

time_t parseDate(string datetime_str)
{
  tm tm = {};
  istringstream ss(datetime_str);
  ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");

  if (ss.fail())
  {
    cerr << "Parsing failed!" << endl;
    time_t return_failed = 0;
    return return_failed;
  }

  time_t timestamp = mktime(&tm);
  return timestamp;
}

void afficher_test(int numero, const string &titre, const auto &res)
{
  cout << "==========================================" << endl;
  cout << "|           Test #" << setw(2) << setfill('0') << numero << " - " << titre << "           |" << endl;
  cout << "------------------------------------------" << endl;
  cout << "| Resultat : " << res << endl;
  cout << "==========================================" << endl
       << endl;
}



// permet que ce main ne s'exécute que si le fichier est exécuté seul 
// sinon erreur de multiple definition of main 
#ifdef COMPILE_TEMP_MAIN
int main()
{
  // --------------------------- Test MoyenneQualiteAir(lat, long, rayon, debut, fin)

  // TEST 1 -- Aucun capteur dans le rayon
  float lat = 41.4, lon = -90.6, perimeter = 5.0;
  time_t debut = parseDate("2019-02-14 12:00:00");
  time_t fin = 0;
  Application app = Application();
  app.moyenneQualiteAir(lat, lon, debut, fin, perimeter);
  return 0;
}
#endif
