#ifndef VISTA_H
#define VISTA_H
#include <iostream>
#include <SFML/Graphics.hpp>
class Vista
{
  private:
    sf::RenderWindow window;
    bool rightButton;
    bool leftButton;
  public:
    Vista();
    bool getRightButton();
    bool getLeftButton();
    sf::RenderWindow& getWindow();
    void update();
}; 
#endif
