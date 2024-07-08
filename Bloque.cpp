#include "Bloque.h"
Bloque::Bloque():vel(5)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
Bloque::Bloque(float inicialX, float inicialY):vel(5), x(inicialX), y(inicialY), gen(rd()), d(0.4)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
  isDibujado = d(gen);
}
void Bloque::gravity()
{
  y += vel;
  if(y >= 720)
  {
    y = 0;
    isDibujado = d(gen);
  }
  shape.setPosition(x, y);
}
void Bloque::draw(sf::RenderWindow& window)
{
  if (isDibujado)
    window.draw(shape);
}
float Bloque::getY()
{
  return y;
}


