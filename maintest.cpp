// main.cpp
#include <iostream>
#include <ctime>
#include <functional> // pour std::invoke
#include <vector>
#include "Application.h"
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
  // Attributs réutilisables
  Attribut attO3{"O3", "µg/m³", "Ozone"};
  Attribut attNO2{"NO2", "µg/m³", "Dioxyde d'azote"};

  // Lambda pour exécuter et afficher un test de listerCapteursSimilaires
  auto runTest = [&](const std::string &titre, Application &app, Capteur &ref)
  {
    std::cout << titre << "\n";
    double duree = mesurerTempsExecution(
        &Application::listerCapteursSimilaires, &app, ref);
    std::cout << "  Temps d'exécution : " << duree << " s\n";

    auto results = app.listerCapteursSimilaires(ref);
    std::cout << "  Nombre de capteurs similaires : " << results.size() << "\n";
    for (auto &p : results)
    {
      std::cout << "    ID=" << p.first.getCapteurId()
                << "  distance=" << p.second << "\n";
    }
    std::cout << "----------------------------------------\n";
  };

  // — Test 1 : cas nominal —
  {
    std::cout << "----------------------------------------\n";
    std::cout << "TESTS AVEC PEU DE CAPTEURS DANS LA BASE \n";
    std::cout << "----------------------------------------\n";
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
    std::vector<Mesure> listA;
    for (int i = 0; i < 10; ++i)
      listA.push_back(Mesure{now + i, float(i), attO3});
    Capteur A{1, 0.0, 0.0, true, false, listA};

    // B partage 5 premières
    std::vector<Mesure> listB;
    for (int i = 0; i < 5; ++i)
      listB.push_back(Mesure{now + i, float(i) + 0.1f, attO3});
    Capteur B{2, 0.0, 0.0, true, false, listB};

    // C partage 2 premières
    std::vector<Mesure> listC;
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

  // A PARTIR DU TEST 7 ON PREND EN COMPTE TOUS LES CAPTEURS DE LA BDD
  std::cout << "----------------------------------------\n";
  std::cout << "TESTS AVEC TOUS LES CAPTEURS DANS LA BASE \n";
  std::cout << "----------------------------------------\n";

  return 0;
}