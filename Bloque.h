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
    sf::Font font;
  public:
    sf::Text text;
    Bloque(float, float, const std::string&, sf::Font);
    void gravity(float&);
    void draw(sf::RenderWindow&);
    float getY();
};
#endif
