#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <algorithm>

class Cuadrado {
public:
    Cuadrado(int id, const sf::Texture& texOriginal, const sf::Texture& texPalabra, sf::Vector2f originalPos);
    void draw(sf::RenderWindow& window);
    void moveToTarget(sf::Vector2f targetPos);
    void returnToOriginal();
    bool contains(sf::Vector2f point);
    sf::Vector2f getPosition() const;
    bool isMoved() const;
    void updateOriginalPosition(sf::Vector2f newPos);
    void animateMovement(sf::Vector2f startPos, sf::Vector2f endPos);

private:
    int id;
    sf::Sprite spriteOriginal;
    sf::Sprite spritePalabra;
    sf::Vector2f originalPos;
    sf::Vector2f currentPos;
    bool moved;
    bool animating;
    sf::Vector2f animationStartPos;
    sf::Vector2f animationEndPos;
    sf::Clock animationClock;
    float animationDuration; // Duration of the animation in seconds
};

Cuadrado::Cuadrado(int id, const sf::Texture& texOriginal, const sf::Texture& texPalabra, sf::Vector2f originalPos)
    : id(id), originalPos(originalPos), currentPos(originalPos), moved(false), animating(false), animationDuration(0.5f) {
    spriteOriginal.setTexture(texOriginal);
    spriteOriginal.setPosition(originalPos);
    spriteOriginal.setScale(125.0f / texOriginal.getSize().x, 100.0f / texOriginal.getSize().y); // Reducir el tamaño a la mitad

    spritePalabra.setTexture(texPalabra);
    spritePalabra.setScale(50.0f / texPalabra.getSize().x, 62.5f / texPalabra.getSize().y); // Reducir el tamaño a la mitad
}

void Cuadrado::draw(sf::RenderWindow& window) {
    if (moved) {
        window.draw(spritePalabra);
    } else {
        window.draw(spriteOriginal);
    }

    if (animating) {
        float elapsedTime = animationClock.getElapsedTime().asSeconds();
        float t = elapsedTime / animationDuration;

        if (t >= 1.0f) {
            t = 1.0f;
            animating = false;
        }

        sf::Vector2f newPos = animationStartPos + t * (animationEndPos - animationStartPos);
        if (moved) {
            spritePalabra.setPosition(newPos);
        } else {
            spriteOriginal.setPosition(newPos);
        }
    }
}

void Cuadrado::moveToTarget(sf::Vector2f targetPos) {
    animateMovement(getPosition(), targetPos);
    moved = true;
}

void Cuadrado::returnToOriginal() {
    animateMovement(getPosition(), originalPos);
    moved = false;
}

bool Cuadrado::contains(sf::Vector2f point) {
    if (moved) {
        return spritePalabra.getGlobalBounds().contains(point);
    } else {
        return spriteOriginal.getGlobalBounds().contains(point);
    }
}

sf::Vector2f Cuadrado::getPosition() const {
    return moved ? spritePalabra.getPosition() : spriteOriginal.getPosition();
}

bool Cuadrado::isMoved() const {
    return moved;
}

void Cuadrado::updateOriginalPosition(sf::Vector2f newPos) {
    originalPos = newPos;
    spriteOriginal.setPosition(originalPos);
}

void Cuadrado::animateMovement(sf::Vector2f startPos, sf::Vector2f endPos) {
    animating = true;
    animationStartPos = startPos;
    animationEndPos = endPos;
    animationClock.restart();
}

class Controller2 {
public:
    Controller2(int n);
    void run();

private:
    sf::RenderWindow window;
    std::unique_ptr<sf::Texture> fondoOrdenTexture;
    std::unique_ptr<sf::Sprite> fondoOrdenSprite;
    std::vector<std::unique_ptr<sf::Texture>> imgOrdenTextures;
    std::vector<std::unique_ptr<sf::Texture>> imgPalabraTextures;
    std::unique_ptr<sf::Texture> tablaTexture;
    std::unique_ptr<sf::Sprite> tablaSprite;
    std::unique_ptr<sf::Texture> botonTexture1; // Textura para botón 1
    std::unique_ptr<sf::Texture> botonTexture2; // Textura para botón 2
    sf::Sprite botonSprite; // Sprite para el botón
    sf::RectangleShape redSquare;
    std::vector<Cuadrado> cuadrados;

    int n;
    bool transitioning;
    std::vector<int> selectedIndices;

    void handleEvents();
    void render();
    void organizeImages();
    void moveImage(int index);
    void returnImage(int index);
    void handleRedSquareClick();
    void resultadoPalabra(const std::vector<int>& indices);
};

Controller2::Controller2(int n)
    : window(sf::VideoMode(1200, 800), "SFML Game"), n(n), transitioning(false),
      fondoOrdenTexture(std::make_unique<sf::Texture>()),
      fondoOrdenSprite(std::make_unique<sf::Sprite>()),
      tablaTexture(std::make_unique<sf::Texture>()),
      tablaSprite(std::make_unique<sf::Sprite>()),
      botonTexture1(std::make_unique<sf::Texture>()), // Inicialización de la textura para botón 1
      botonTexture2(std::make_unique<sf::Texture>()) { // Inicialización de la textura para botón 2

    fondoOrdenTexture->loadFromFile("img/fondoOrden.png");
    fondoOrdenSprite->setTexture(*fondoOrdenTexture);

    for (int i = 0; i < n * n; ++i) {
        imgOrdenTextures.push_back(std::make_unique<sf::Texture>());
        imgPalabraTextures.push_back(std::make_unique<sf::Texture>());

        imgOrdenTextures[i]->loadFromFile("img/imgOrden" + std::to_string(i + 1) + ".png");
        imgPalabraTextures[i]->loadFromFile("img/imgPalabra" + std::to_string(i + 1) + ".png");

        float x = (i % n) * (window.getSize().x * 2 / 4 / n) + 40;
        float y = (i / n) * (window.getSize().y * 4 / 6 / n) + 40;
        sf::Vector2f originalPos(x, y);

        cuadrados.emplace_back(i, *imgOrdenTextures[i], *imgPalabraTextures[i], originalPos);
    }

    tablaTexture->loadFromFile("img/Tabla.png");
    tablaSprite->setTexture(*tablaTexture);
    tablaSprite->setPosition(window.getSize().x * 2 / 3, 100);

    botonTexture1->loadFromFile("img/boton1.png"); // Cargar la textura del botón 1
    botonTexture2->loadFromFile("img/boton2.png"); // Cargar la textura del botón 2
    botonSprite.setTexture(*botonTexture1); // Inicialmente establecer el botón con textura 1
    botonSprite.setScale(50.0f / botonTexture1->getSize().x, 50.0f / botonTexture1->getSize().y); // Ajustar tamaño del botón
    botonSprite.setPosition(window.getSize().x * 2 / 3 - 25, 500);

    redSquare.setSize(sf::Vector2f(80, 80));
    redSquare.setFillColor(sf::Color::Transparent);
    redSquare.setPosition(window.getSize().x * 2 / 3 + 25, 500);
}

void Controller2::run() {
    while (window.isOpen()) {
        handleEvents();
        render();
    }
}

void Controller2::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!transitioning) {
                transitioning = true;
            } else {
                int countMoving = 0;
                for (int i = 0; i < n * n; ++i) {
                    if (cuadrados[i].contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (!cuadrados[i].isMoved()) {
                            if (countMoving < 3) {
                                moveImage(i);
                                selectedIndices.push_back(i + 1);
                                ++countMoving;
                            }
                        } else {
                            returnImage(i);
                        }
                    }
                }
                if (redSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    handleRedSquareClick();
                    botonSprite.setTexture(*botonTexture2); // Cambiar textura a botón 2
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (redSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                botonSprite.setTexture(*botonTexture1); // Volver a la textura del botón 1
            }
        }
    }
}

void Controller2::organizeImages() {
    window.draw(*fondoOrdenSprite);
    for (auto& cuadrado : cuadrados) {
        cuadrado.draw(window);
    }
    window.draw(*tablaSprite);
    botonSprite.setPosition(redSquare.getPosition().x , redSquare.getPosition().y); // Posicionar el botón a la derecha del cuadrado rojo
    window.draw(botonSprite); // Dibujar el botón según la textura actual
    window.draw(redSquare);
}

void Controller2::moveImage(int index) {
    sf::Vector2f targetPos(100 + 100 * selectedIndices.size(), 600);
    cuadrados[index].moveToTarget(targetPos);
}

void Controller2::returnImage(int index) {
    cuadrados[index].returnToOriginal();
    selectedIndices.erase(std::remove(selectedIndices.begin(), selectedIndices.end(), index + 1), selectedIndices.end());
    // Reorganizar las imágenes en movimiento para llenar los espacios
    int count = 0;
    for (int i : selectedIndices) {
        sf::Vector2f newTargetPos(100 + 100 * count, 600);
        cuadrados[i - 1].moveToTarget(newTargetPos);
        ++count;
    }
}

void Controller2::handleRedSquareClick() {
    resultadoPalabra(selectedIndices);
}

void Controller2::resultadoPalabra(const std::vector<int>& indices) {
    std::string palabras[19] = {"SELECT", "*", "FROM", "producto","nombre", 
    "descripcion", "precio", "orden","id", "user_id", "amount", "date",
    "persona", "nombre", "apellidos", "dni", "users","name", "age"};

    for (int indice : indices) {
        std::cout << palabras[indice - 1] << " ";
    }
    std::cout << std::endl;
}

void Controller2::render() {
    window.clear();
    if (transitioning) {
        organizeImages();
    }
    window.display();
}

int main() {
    int n = 4; // Define el tamaño de la cuadrícula
    Controller2 controller2(n);
    controller2.run();
    return 0;
}
