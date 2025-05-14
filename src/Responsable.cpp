using namespace std;
#include "Personne.cpp"
#include <iostream>
#include <string>

class Responsable : public Personne
{
public:
    Responsable(string id, string str) : Personne(id, str) {}
    ~Responsable() {}
};
