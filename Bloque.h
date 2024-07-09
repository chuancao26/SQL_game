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
    float vel;
  public:
    Bloque();
    Bloque(float, float);
    void gravity(float&);
    void draw(sf::RenderWindow&);
    float getY();
};
#endif
