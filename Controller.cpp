#include "Controller.h"
Controller::Controller(): cantBloques(10), bloques(10)
{
  for(int i = 0; i < cantBloques; i++)
  {
    bloques[i] = new Bloque();
  }
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
    view.update();
    if(view.getRightButton())
    {
      player.moveRight();
    }
    if(view.getLeftButton())
    {
      player.moveLeft();
    }
    for(int i = 0; i < cantBloques; i++)
    {
      bloques[i] -> gravity();
    }
    renderizar();
  }
}
void Controller::renderizar()
{
  view.window.clear();
  player.draw(view.window);
  for(int i = 0; i < cantBloques; i++)
  {
    bloques[i] -> draw(view.window);
  }
  view.window.display();
}
