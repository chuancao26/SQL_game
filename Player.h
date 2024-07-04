#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
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
