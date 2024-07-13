#include "Controller.h"
Controller::Controller(): camarero(1280, 720, font)
{
  font.loadFromFile("fonts/Arial.ttf");
}
void Controller::update()
{
    float deltaTime = clock.restart().asSeconds();
    if(view.getRightButton())
    {
      player.moveRight(deltaTime);
    }
    if(view.getLeftButton())
    {
      player.moveLeft(deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
      camarero.setMapSelector("q");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      camarero.setMapSelector("w");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
      camarero.setMapSelector("e");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
      camarero.setMapSelector("r");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      camarero.spaceClean();
    view.update();
    camarero.update(deltaTime);
    camarero.colisiones(player.shape, analyzer);
}
void Controller::run()
{
  while(view.window.isOpen())
  {
    sf::Event event;
    while (view.window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed)
	      view.window.close();
    }
    update();
    renderizar();
  }
}
void Controller::renderizar()
{
  view.window.clear();
  view.setBackground();
  player.draw(view.window);
  camarero.draw(view.window);
  view.window.display();
}
