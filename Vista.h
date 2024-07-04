#ifndef VISTA_H
#define VISTA_H
#include <SFML/Graphics.hpp>
class Vista
{
  private:
    bool rightButton;
    bool leftButton;
  public:
    Vista();
    sf::RenderWindow window;
    bool getRightButton();
    bool getLeftButton();
    void update();
}; 
#endif
