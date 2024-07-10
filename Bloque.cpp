#include "Bloque.h"

Bloque::Bloque(float inicialX, float inicialY, const std::string& word, const sf::Font& font)
    : vel(200.f), x(inicialX), y(inicialY)
{
    text.setFont(font);
    text.setString(word);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setPosition(x, y);
}

void Bloque::gravity(float deltaTime)
{
    y += vel * deltaTime;
    text.setPosition(x, y);
}

void Bloque::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

float Bloque::getY() const
{
    return y;
}

