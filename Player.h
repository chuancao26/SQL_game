#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player
{
private:
    float x;
    float y;
    float vel;
    sf::Texture texture;

public:
    sf::Sprite shape;
    Player(); 
    void moveLeft(float&);
    void moveRight(float&);
    void draw(sf::RenderWindow&);
};

#endif
