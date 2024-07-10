#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Player
{
  private:
    sf::RectangleShape shape;
    float x;
    float y;
    float vel;
  public:
    Player(); 
    void moveLeft(float&);
    void moveRight(float&);
    void draw(sf::RenderWindow&);
};
#endif
