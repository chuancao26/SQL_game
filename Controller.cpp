#include <iostream>
#include "Vista.h"
#include "Player.h"
class Controller
{
  private:
    Vista view;
    Player player;
    sf::RenderWindow& window;
  public:
    Controller();
    void run()
    {
      while(view.getWindow().isOpen())
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
      }
      renderizar();
    }
    void renderizar()
    {
      view.getWindow().clear();
      player.draw(view.getWindow());
      view.getWindow().display();
    }
};
