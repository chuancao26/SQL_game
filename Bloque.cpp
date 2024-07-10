#include "Bloque.h"
Bloque::Bloque():vel(200)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
Bloque::Bloque(float inicialX, float inicialY):vel(200.f), x(inicialX), y(inicialY)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
void Bloque::gravity(float& deltaTime)
{
  y += vel * deltaTime;
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


