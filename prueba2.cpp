#include <SFML/Graphics.hpp>
#include "Bloque.cpp"
#include <iostream>
using namespace std;
int main()
{
  sf::Font font;
  sf::Clock clock;
  string word = "hola";
  Bloque bloque(100, 0, word);
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	float deltaTime = clock.restart().asSeconds();
	bloque.gravity(deltaTime);
        window.clear();
        window.draw(shape);
	window.draw(bloque.text);
        window.display();
    }

    return 0;
}
