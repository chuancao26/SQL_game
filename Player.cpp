#include "Player.h"

Player::Player(): vel(500), x(600), y(600)
{
    if (!texture.loadFromFile("img/Camarero/avion.png"))
    {
      cerr << "error" << endl;
    }
    
    shape.setTexture(texture);
    
    // Ajusta el origen del shape al centro de la imagen
    shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
    shape.setScale(0.1f, 0.1f);
    shape.setPosition(x, y);
}

void Player::moveLeft(float& deltaTime)
{
    if (x > 0)
    {
        x -= vel * deltaTime;
        shape.setPosition(x, y);
    }
}

void Player::moveRight(float& deltaTime)
{
    if(x < 1280)
    {
        x += vel * deltaTime;
        shape.setPosition(x, y);
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
