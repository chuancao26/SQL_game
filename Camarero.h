#ifndef CAMARERO_H
#define CAMARERO_H
#include <random>
class Camarero
{
  private:
    vector<vector<Bloque*>> bloques;
    int cantFil;
    int cantCol;
    int limiteX;
    int limiteY;
    random_device rd;
    mt19937 gen;
    bernoulli_distribution d;
  public:
    Camarero();
    void draw();
};
#endif
