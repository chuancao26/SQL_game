#include "Player.h"
Player::Player(): vel(1.0f), x(600), y(600)
{
  shape.setSize(sf::Vector2f(20.0f, 20.0f));
  shape.setFillColor(sf::Color::White);
  shape.setPosition(x, y);
}
void Player::moveLeft()
{
  x -= vel;
  shape.setPosition(x, y);
}
void Player::moveRight()
{
  x += vel;
  shape.setPosition(x, y);
}
void Player::draw(sf::RenderWindow& window)
{
  window.draw(shape);
}

