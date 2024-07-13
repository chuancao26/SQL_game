#ifndef VISTA_H
#define VISTA_H
#include <SFML/Graphics.hpp>
class Vista
{
  private:
    bool rightButton;
    bool leftButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

  public:
    Vista();
    sf::RenderWindow window;
    bool getRightButton();
    bool getLeftButton();
    void update();
    void setBackground();
}; 
#endif
