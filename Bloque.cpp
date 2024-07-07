#include "Bloque.h"
Bloque::Bloque():vel(5)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
Bloque::Bloque(float inicialX, float inicialY):vel(5), x(inicialX), y(inicialY), gen(rd()), d(0.3)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
void Bloque::gravity()
{
  y += vel;
  if(y >= 735)
  {
    y = -20;
  }
  shape.setPosition(x, y);
}
void Bloque::draw(sf::RenderWindow& window)
{
  window.draw(shape);
}
float Bloque::getY()
{
  return y;
}


