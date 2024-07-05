#include "Vista.h"
Vista::Vista(): window(sf::VideoMode(1280, 720), "SQL") 
{
  window.setFramerateLimit(60);
}
void Vista::update()
{
  rightButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
  leftButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}
bool Vista::getRightButton()
{
  return rightButton;
}
bool Vista::getLeftButton()
{
  return leftButton;
}
