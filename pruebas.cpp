#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
struct CuadradoPequeno {
    sf::RectangleShape shape;
    float velocidad;

    CuadradoPequeno(float x, float y) {
        shape.setSize(sf::Vector2f(20.0f, 20.0f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        velocidad = 0.10f;  // Puedes ajustar la velocidad si quieres
    }

    void mover() {
        shape.move(0.0f, velocidad);
    }
};

int main()
{
    // Inicializar generador de números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Mover Cuadrado");

    // Crear el cuadrado grande
    sf::RectangleShape cuadrado(sf::Vector2f(50.0f, 50.0f));
    cuadrado.setFillColor(sf::Color::Blue);
    cuadrado.setPosition(600.0f, 600.0f);

    // Vector para almacenar los cuadrados pequeños
    std::vector<CuadradoPequeno> cuadradosPequenos;

    // Ejecutar el bucle principal
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

	cout << sf::Keyboard::isKeyPressed(sf::Keyboard::Right) << " -- " << sf::Keyboard::isKeyPressed(sf::Keyboard::Left) << endl;
        // Mover el cuadrado grande con las flechas del teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cuadrado.move(1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            cuadrado.move(-1.0f, 0.0f);
        }

        // Generar nuevos cuadrados pequeños de forma aleatoria
        if (std::rand() % 100 == 0) {  // Ajusta la frecuencia si es necesario
            float x = static_cast<float>(std::rand() % 1230 + 20);
            cuadradosPequenos.push_back(CuadradoPequeno(x, 0.0f));
        }

        // Mover los cuadrados pequeños
        for (auto& cuadradito : cuadradosPequenos) {
            cuadradito.mover();
        }

        // Eliminar los cuadrados que hayan llegado al fondo de la ventana
        cuadradosPequenos.erase(std::remove_if(cuadradosPequenos.begin(), cuadradosPequenos.end(),
            [](const CuadradoPequeno& c) {
                return c.shape.getPosition().y > 740.0f;
            }), cuadradosPequenos.end());

        // Limpiar la ventana
        window.clear(sf::Color::White);

        // Dibujar el cuadrado grande
        window.draw(cuadrado);

        // Dibujar los cuadrados pequeños
        for (const auto& cuadradito : cuadradosPequenos) {
            window.draw(cuadradito.shape);
        }

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}

