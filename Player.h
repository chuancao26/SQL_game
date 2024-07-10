#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Player
{
  private:
    float x;
    float y;
    float vel;
  public:
    Player(); 
    sf::RectangleShape shape;
    void moveLeft(float&);
    void moveRight(float&);
    void draw(sf::RenderWindow&);
};
#endif
