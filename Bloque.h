#ifndef BLOQUE_H
#define BLOQUE_H

#include <SFML/Graphics.hpp>
#include <string>

class Bloque {
public:
    Bloque(float inicialX, float inicialY, const std::string& word, const sf::Font& font);

    void gravity(float deltaTime);
    void draw(sf::RenderWindow& window);
    float getY() const;

    sf::Text text;

private:
    float vel;
    float x;
    float y;
};

#endif // BLOQUE_H

