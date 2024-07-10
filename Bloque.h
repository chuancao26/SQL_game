#ifndef BLOQUE_H
#define BLOQUE_H
#include <vector>
#include <random>
class Bloque
{
  private:
    float x;
    float y;
    float vel;
  public:
    sf::RectangleShape shape;
    Bloque();
    Bloque(float, float);
    void gravity(float&);
    void draw(sf::RenderWindow&);
    float getY();
};
#endif
