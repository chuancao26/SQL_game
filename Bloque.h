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
    sf::Text text;
    Bloque(float, float, string, const sf::Font& font);
    void gravity(float);
    void draw(sf::RenderWindow&);
    float getY();
    string getWord();
};
#endif
