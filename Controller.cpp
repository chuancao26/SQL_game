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
