#ifndef BLOQUE_H
#define BLOQUE_H
#include <vector>
#include <random>
class Bloque
{
  private:
    sf::RectangleShape shape;
    float x;
    float y;
    bool isDibujado;
    float vel;
    random_device rd;
    mt19937 gen;
    bernoulli_distribution d;
  public:
    Bloque();
    Bloque(float, float);
    void gravity();
    void draw(sf::RenderWindow&);
    float getY();
};
#endif
