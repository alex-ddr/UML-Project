// main.cpp
#include <iostream>
#include <ctime>
#include <functional> // pour std::invoke
#include <vector>
#include <string>
#include "Application.h"
#include "Parser.h"

using namespace std;
#include "Capteur.h"
#include "Mesure.h"

template <typename Func, typename... Args>
double mesurerTempsExecution(Func &&func, Args &&...args)
{
  clock_t start = clock();
  std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
  clock_t end = clock();
  return double(end - start) / CLOCKS_PER_SEC;
}

int main()
{
  Attribut attO3 = {"O3", "µg/m³", "Ozone"};
  Attribut attNO2 = {"NO2", "µg/m³", "Dioxyde d'azote"};

  // Lambda de test
  auto runTest = [&](const std::string &titre, Application &app, Capteur &ref)
  {
    cout << titre << "\n";
    double duree = mesurerTempsExecution(
        &Application::listerCapteursSimilaires, &app, ref);
    cout << "  Temps d'exécution : " << duree << " s\n";

    auto res = app.listerCapteursSimilaires(ref);
    std::cout << "  Nombre de capteurs similaires : " << res.size() << "\n";
    for (auto &p : res)
    {
      cout << "    ID=" << p.first.getCapteurId()
           << "  distance=" << p.second << "\n";
    }
    cout << "----------------------------------------\n";
  };
  // ---------------------------------------------------------------------------------------
  cout << "Tests de listerCapteursSimilaires\n";
  cout << "----------------------------------------\n";
  cout << "Test sur peu capteurs\n";

  // TEST 1 – cas nominal
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA1(now, 10.0f, attO3);
    Mesure mA2(now + 1, 20.0f, attNO2);
    Capteur A("1", 0.0f, 0.0f, true, false, std::vector<Mesure>{mA1, mA2});

    Mesure mB1(now, 10.5f, attO3);
    Mesure mB2(now + 1, 19.8f, attNO2);
    Capteur B("2", 0.0f, 0.0f, true, false, std::vector<Mesure>{mB1, mB2});

    app.ajouterCapteur(A);
    app.ajouterCapteur(B);
    runTest("Test 1 – Cas nominal", app, A);
  }

  // TEST 2 – aucun timestamp ni attribut commun
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA(now, 50.0f, attO3);
    Capteur A("1", 0.0f, 0.0f, true, false, std::vector<Mesure>{mA});

    Mesure mC(now + 3600, 80.0f, attNO2);
    Capteur C("3", 0.0f, 0.0f, true, false, std::vector<Mesure>{mC});

    app.ajouterCapteur(A);
    app.ajouterCapteur(C);
    runTest("Test 2 – Aucun timestamp/attribut commun", app, A);
  }

  // TEST 3 – référence unique
  {
    Application app;
    Capteur A("1", 0.0f, 0.0f, true, false, std::vector<Mesure>{});
    app.ajouterCapteur(A);
    runTest("Test 3 – Référence unique", app, A);
  }

  // TEST 4 – partiellement communs
  {
    Application app;
    time_t now = time(nullptr);
    std::vector<Mesure> listA;
    for (int i = 0; i < 10; ++i)
      listA.emplace_back(now + i, float(i), attO3);
    Capteur A("1", 0.0f, 0.0f, true, false, listA);

    std::vector<Mesure> listB;
    for (int i = 0; i < 5; ++i)
      listB.emplace_back(now + i, float(i) + 0.1f, attO3);
    Capteur B("2", 0.0f, 0.0f, true, false, listB);

    std::vector<Mesure> listC;
    for (int i = 0; i < 2; ++i)
      listC.emplace_back(now + i, float(i) + 0.2f, attO3);
    Capteur C("3", 0.0f, 0.0f, true, false, listC);

    app.ajouterCapteur(A);
    app.ajouterCapteur(B);
    app.ajouterCapteur(C);
    runTest("Test 4 – Partiellement communs", app, A);
  }

  // TEST 5 – capteur non fiable ignoré
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA(now, 5.0f, attO3);
    Capteur A("1", 0.0f, 0.0f, true, false, std::vector<Mesure>{mA});

    Mesure mD(now, 5.0f, attO3);
    Capteur D("4", 0.0f, 0.0f, false, false, std::vector<Mesure>{mD});

    app.ajouterCapteur(A);
    app.ajouterCapteur(D);
    runTest("Test 5 – Capteur non fiable", app, A);
  }

  // TEST 6 – mesures parfaitement identiques
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA1(now, 15.0f, attO3);
    Mesure mA2(now + 1, 25.0f, attNO2);
    Capteur A("1", 0.0f, 0.0f, true, false, std::vector<Mesure>{mA1, mA2});
    Capteur E("5", 0.0f, 0.0f, true, false, std::vector<Mesure>{mA1, mA2});

    app.ajouterCapteur(A);
    app.ajouterCapteur(E);
    runTest("Test 6 – Mesures identiques", app, A);
  }
  cout << "----------------------------------------\n";
  cout << "Test toute la bdd\n";
  cout << "----------------------------------------\n";
  // Chargement de la base de données
  Application appli;
  appli.chargerDonnees("./data/sensors.csv", "./data/users.csv", "./data/attributes.csv", "./data/measurements.csv");
  // Test sur toute la base de données
  runTest("Test toute la bdd", appli, appli.getListeTousLesCapteurs().front());
  printf("premier capteur : %s\n", appli.getListeTousLesCapteurs().front().getCapteurId().c_str());
  cout << "----------------------------------------\n";
  cout << "Tests de moyenneQualiteAir\n";
  cout << "----------------------------------------\n";

  // ---------------------------------------------------------------------------------------
  //
  // Lambda pour exécuter et afficher un test de MoyenneQualiteAir
  auto runTest2 = [&](const string &titre, Application &app, float lat, float lon, time_t debut, time_t fin, float rayon)
  {
    cout << titre << "\n";
    double duree = mesurerTempsExecution(
        &Application::moyenneQualiteAir, &app, lat, lon, debut, fin, rayon);
    cout << "  Temps d'exécution : " << duree << " s\n";

    auto results = app.moyenneQualiteAir(lat, lon, debut, fin, rayon);
    cout << "  Moyenne qualité air :" << "\n";
    for (const auto &p : results)
    {
      cout << "    " << p.first << " : " << p.second << "\n";
    }
    cout << "----------------------------------------\n";
  };
  Application app;

  // — Test 1 :  Aucun capteur dans le rayon peu import le timestap
  float lat = 41.4, lon = -90.6, perimeter = 5.0;
  time_t debut = Parser::parseDate("2019-02-14 12:00:00");
  time_t fin = 0;
  runTest2("Test 1 – Aucun capteur dans le rayon peu import le timestap", app, lat, lon, debut, fin, perimeter);

  // — Test 2 : Un ou plusieurs capteurs dans le rayon pour un timestamp valide
  lat = 44.8, lon = 4.6, perimeter = 10.0;
  debut = Parser::parseDate("2019-02-04 12:00:00");
  fin = debut + 24 * 3600 * 7;
  runTest2("Test 2 – Un ou plusieurs capteurs dans le rayon pour un timestamp valide", app, lat, lon, debut, fin, perimeter);
  return 0;
}