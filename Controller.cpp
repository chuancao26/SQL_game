#include "Controller.h"
Controller::Controller()
{
}
void Controller::run()
{
      while(view.window.isOpen())
      {
	view.update();
	if(view.getRightButton())
	{
	  player.moveRight();
	}
	if(view.getLeftButton())
	{
	  player.moveLeft();
	}
      renderizar();
      }
}
void Controller::renderizar()
{
  view.window.clear();
  player.draw(view.window);
  view.window.display();
}
