#include "Vista.h"
Vista::Vista(): window(sf::VideoMode(1280, 720), "SQL")
{
  window.setFramerateLimit(120);
  backgroundTexture.loadFromFile("img/Camarero/background.jpg");
  backgroundSprite.setTexture(backgroundTexture);
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
void Vista::setBackground()
{
  window.draw(backgroundSprite);
}

