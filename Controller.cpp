#include "Controller.h"
Controller::Controller(): camarero(1280, 720)
{
}
void Controller::update()
{
    if(view.getRightButton())
    {
      player.moveRight();
    }
    if(view.getLeftButton())
    {
      player.moveLeft();
    }
    view.update();
    camarero.update();
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
  player.draw(view.window);
  camarero.draw(view.window);
  view.window.display();
}
