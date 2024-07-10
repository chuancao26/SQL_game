#include "Player.h"
Player::Player(): vel(500), x(600), y(600)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(x, y);
}
void Player::moveLeft(float& deltaTime)
{
  if (x > 0)
    x -= vel * deltaTime;
  shape.setPosition(x, y);
}
void Player::moveRight(float& deltaTime)
{
  if(x < 1280)
    x += vel * deltaTime;
  shape.setPosition(x, y);
}
void Player::draw(sf::RenderWindow& window)
{
  window.draw(shape);
}

