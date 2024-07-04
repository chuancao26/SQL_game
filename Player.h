#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class Player
{
  private:
    sf::RectangleShape shape;
    int x;
    int y;
    float vel;
  public:
    Player(); 
    void moveLeft();
    void moveRight();
    void draw(sf::RenderWindow&);
};
#endif
