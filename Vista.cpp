#include "Vista.h"
Vista::Vista(): window(sf::VideoMode(1280, 720), "SQL")
{
  window.setFramerateLimit(120);
  backgroundTexture.loadFromFile("img/menu/menu.png");
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
void Vista::setBackground(int nivel)
{
  if(nivel==1){
    backgroundTexture.loadFromFile("img/menu/menu.png");
  }else if(nivel==2){
    backgroundTexture.loadFromFile("img/Camarero/background.jpg");
  }else if(nivel==3){
    backgroundTexture.loadFromFile("img/menu/menu.png");
  }
  window.draw(backgroundSprite);
}

