#include "Vista.h"
Vista::Vista(): window(sf::VideoMode(1280, 720), "SQL"), shape(100.f)
{
  shape.setFillColor(sf::Color::Green);
}
void Vista::ejecutar()
{
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(shape);
    window.display();
  }
}

