#include "Bloque.h"
Bloque::Bloque():vel(5), arr(10), yInicio(5)
{
  std::srand(std::time(0));
  for(int i = 0; i < 10; i++)
  {
    arr[i] = 1280/10 * i;
  }
  yInicio = {-50, -100, -200, -10, -250, -300};
  int random_number = std::rand();
  x = arr[random_number % 10];
  y = yInicio[random_number % 5];
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(x, y);
}
void Bloque::gravity()
{
  y += vel;
  if(y >= 735)
  {
    int random_number = std::rand();
    x = arr[random_number % 10];
    y = -20 - random_number % 1000;
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


