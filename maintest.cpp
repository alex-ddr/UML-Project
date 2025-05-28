#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "Application.h"
#include "Parser.h"

using namespace std;

template <typename Func, typename... Args>
double mesurerTempsExecution(Func func, Args &&...args)
{
  clock_t start = clock();
  func(forward<Args>(args)...);
  clock_t end = clock();
  return static_cast<double>(end - start) / CLOCKS_PER_SEC;
}

int main()
{
  // Attributs réutilisables
  Attribut attO3{"O3", "µg/m³", "Ozone"};
  Attribut attNO2{"NO2", "µg/m³", "Dioxyde d'azote"};

  // Lambda pour exécuter et afficher un test de listerCapteursSimilaires
  auto runTest = [&](const string &titre, Application &app, Capteur &ref)
  {
    cout << titre << "\n";
    double duree = mesurerTempsExecution(
        &Application::listerCapteursSimilaires, &app, ref);
    cout << "  Temps d'exécution : " << duree << " s\n";

    auto results = app.listerCapteursSimilaires(ref);
    cout << "  Nombre de capteurs similaires : " << results.size() << "\n";
    for (auto &p : results)
    {
      cout << "    ID=" << p.first.getCapteurId()
           << "  distance=" << p.second << "\n";
    }
    cout << "----------------------------------------\n";
  };

  // — Test 1 : cas nominal —
  {
    Application app;
    time_t now = time(nullptr);

    // Capteur A — mesures O3/NO2
    Mesure mA1{now, 10.0f, attO3};
    Mesure mA2{now + 1, 20.0f, attNO2};
    Capteur A{1, 0.0, 0.0, true, false, {mA1, mA2}};

    // Capteur B — très similaire
    Mesure mB1{now, 10.5f, attO3};
    Mesure mB2{now + 1, 19.8f, attNO2};
    Capteur B{2, 0.0, 0.0, true, false, {mB1, mB2}};

    app.ajouterCapteur(A);
    app.ajouterCapteur(B);
    runTest("Test 1 – Cas nominal", app, A);
  }

  // — Test 2 : aucun timestamp/attribut commun —
  {
    Application app;
    time_t now = time(nullptr);

    // A mesure O3 à now
    Mesure mA{now, 50.0f, attO3};
    Capteur A{1, 0.0, 0.0, true, false, {mA}};

    // C mesure NO2 à now+3600
    Mesure mC{now + 3600, 80.0f, attNO2};
    Capteur C{3, 0.0, 0.0, true, false, {mC}};

    app.ajouterCapteur(A);
    app.ajouterCapteur(C);
    runTest("Test 2 – Aucun timestamp/attribut commun", app, A);
  }

  // — Test 3 : seul capteur dans le système —
  {
    Application app;
    // A sans mesure
    Capteur A{1, 0.0, 0.0, true, false, {}};
    app.ajouterCapteur(A);
    runTest("Test 3 – Référence unique", app, A);
  }

  // — Test 4 : partiellement communs (5 pts vs 2 pts) —
  {
    Application app;
    time_t now = time(nullptr);
    // A a 10 mesures O3
    vector<Mesure> listA;
    for (int i = 0; i < 10; ++i)
      listA.push_back(Mesure{now + i, float(i), attO3});
    Capteur A{1, 0.0, 0.0, true, false, listA};

    // B partage 5 premières
    vector<Mesure> listB;
    for (int i = 0; i < 5; ++i)
      listB.push_back(Mesure{now + i, float(i) + 0.1f, attO3});
    Capteur B{2, 0.0, 0.0, true, false, listB};

    // C partage 2 premières
    vector<Mesure> listC;
    for (int i = 0; i < 2; ++i)
      listC.push_back(Mesure{now + i, float(i) + 0.2f, attO3});
    Capteur C{3, 0.0, 0.0, true, false, listC};

    app.ajouterCapteur(A);
    app.ajouterCapteur(B);
    app.ajouterCapteur(C);
    runTest("Test 4 – Partiellement communs", app, A);
  }

  // — Test 5 : non fiable ignoré —
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA{now, 5.0f, attO3};
    Capteur A{1, 0.0, 0.0, true, false, {mA}};

    Mesure mD{now, 5.0f, attO3};
    Capteur D{4, 0.0, 0.0, false, false, {mD}};

    app.ajouterCapteur(A);
    app.ajouterCapteur(D);
    runTest("Test 5 – Capteur non fiable", app, A);
  }

  // — Test 6 : mesures parfaitement identiques —
  {
    Application app;
    time_t now = time(nullptr);

    Mesure mA1{now, 15.0f, attO3};
    Mesure mA2{now + 1, 25.0f, attNO2};
    Capteur A{1, 0.0, 0.0, true, false, {mA1, mA2}};

    // E a exactement les mêmes mesures
    Capteur E{5, 0.0, 0.0, true, false, {mA1, mA2}};

    app.ajouterCapteur(A);
    app.ajouterCapteur(E);
    runTest("Test 6 – Mesures identiques", app, A);
  }

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
    cout << "  Moyenne qualité air " << results.size() << "\n";
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