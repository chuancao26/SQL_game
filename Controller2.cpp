#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>

class Controller2 {
public:
    Controller2(int n);
    void run();

private:
    sf::RenderWindow window;
    std::unique_ptr<sf::Texture> fondoOrdenTexture;
    std::unique_ptr<sf::Sprite> fondoOrdenSprite;
    std::vector<std::unique_ptr<sf::Texture>> imgOrdenTextures;
    std::vector<std::unique_ptr<sf::Sprite>> imgOrdenSprites;
    std::vector<std::unique_ptr<sf::Texture>> imgPalabraTextures;
    std::vector<std::unique_ptr<sf::Sprite>> imgPalabraSprites;
    std::unique_ptr<sf::Texture> tablaTexture;
    std::unique_ptr<sf::Sprite> tablaSprite;
    sf::RectangleShape redSquare;

    int n;
    bool transitioning;
    std::vector<int> selectedIndices;
    std::vector<bool> imgMoved;
    std::vector<sf::Vector2f> originalPositions;

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
      imgMoved(n * n, false),
      originalPositions(n * n) {

    fondoOrdenTexture->loadFromFile("img/fondoOrden.png");
    fondoOrdenSprite->setTexture(*fondoOrdenTexture);

    for (int i = 0; i < n * n; ++i) {
        imgOrdenTextures.push_back(std::make_unique<sf::Texture>());
        imgOrdenSprites.push_back(std::make_unique<sf::Sprite>());
        imgPalabraTextures.push_back(std::make_unique<sf::Texture>());
        imgPalabraSprites.push_back(std::make_unique<sf::Sprite>());

        imgOrdenTextures[i]->loadFromFile("img/imgOrden" + std::to_string(i + 1) + ".png");
        imgOrdenSprites[i]->setTexture(*imgOrdenTextures[i]);
        imgOrdenSprites[i]->setScale(250.0f / imgOrdenTextures[i]->getSize().x, 200.0f / imgOrdenTextures[i]->getSize().y);
        
        float x = (i % n) * (window.getSize().x * 2 / 3 / n) + 20;
        float y = (i / n) * (window.getSize().y * 4 / 5 / n) + 20;
        imgOrdenSprites[i]->setPosition(x, y);
        originalPositions[i] = imgOrdenSprites[i]->getPosition();
        
        imgPalabraTextures[i]->loadFromFile("img/imgPalabra" + std::to_string(i + 1) + ".png");
        imgPalabraSprites[i]->setTexture(*imgPalabraTextures[i]);
    }

    tablaTexture->loadFromFile("img/Tabla.png");
    tablaSprite->setTexture(*tablaTexture);
    tablaSprite->setPosition(window.getSize().x * 2 / 3, 100);

    redSquare.setSize(sf::Vector2f(50, 50));
    redSquare.setFillColor(sf::Color::Red);
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
                for (int i = 0; i < n * n; ++i) {
                    if (imgOrdenSprites[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (!imgMoved[i]) {
                            moveImage(i);
                            selectedIndices.push_back(i + 1);
                        } else {
                            returnImage(i);
                        }
                    }
                }
                if (redSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    handleRedSquareClick();
                }
            }
        }
    }
}

void Controller2::organizeImages() {
    window.draw(*fondoOrdenSprite);
    for (int i = 0; i < n * n; ++i) {
        window.draw(*imgOrdenSprites[i]);
    }
    window.draw(*tablaSprite);
    window.draw(redSquare);
}

void Controller2::moveImage(int index) {
    imgOrdenSprites[index]->setTexture(*imgPalabraTextures[index]);
    imgOrdenSprites[index]->setScale(100.0f / imgPalabraTextures[index]->getSize().x, 125.0f / imgPalabraTextures[index]->getSize().y);

    sf::Vector2f startPosition = imgOrdenSprites[index]->getPosition();
    sf::Vector2f targetPosition(100 + 100 * selectedIndices.size(), 600);

    sf::Clock clock;
    while (imgOrdenSprites[index]->getPosition().y < targetPosition.y) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        sf::Vector2f currentPosition = imgOrdenSprites[index]->getPosition();
        sf::Vector2f distance = targetPosition - startPosition;
        sf::Vector2f newPosition = startPosition + distance * elapsedTime * 0.9f;

        if (newPosition.y >= targetPosition.y) {
            newPosition.y = targetPosition.y;
        }

        imgOrdenSprites[index]->setPosition(newPosition);
        window.clear();
        organizeImages();
        window.display();
    }

    imgMoved[index] = true;
}

void Controller2::returnImage(int index) {
    sf::Vector2f startPosition = imgOrdenSprites[index]->getPosition();
    sf::Vector2f targetPosition = originalPositions[index];

    sf::Clock clock;
    while (imgOrdenSprites[index]->getPosition().y > targetPosition.y) {
        float elapsedTime = clock.getElapsedTime().asSeconds();
        sf::Vector2f currentPosition = imgOrdenSprites[index]->getPosition();
        sf::Vector2f distance = targetPosition - startPosition;
        sf::Vector2f newPosition = startPosition + distance * elapsedTime * 0.9f;

        if (newPosition.y <= targetPosition.y) {
            newPosition.y = targetPosition.y;
        }

        imgOrdenSprites[index]->setPosition(newPosition);
        window.clear();
        organizeImages();
        window.display();
    }

    imgMoved[index] = false;
    selectedIndices.erase(std::remove(selectedIndices.begin(), selectedIndices.end(), index + 1), selectedIndices.end());

    sf::Clock waitClock;
    while (waitClock.getElapsedTime().asSeconds() < 0.5f) {
        // Espera por 0.5 segundos
    }

    imgOrdenSprites[index]->setTexture(*imgOrdenTextures[index]);
    imgOrdenSprites[index]->setScale(250.0f / imgOrdenTextures[index]->getSize().x, 200.0f / imgOrdenTextures[index]->getSize().y);
}

void Controller2::handleRedSquareClick() {
    resultadoPalabra(selectedIndices);
}

void Controller2::resultadoPalabra(const std::vector<int>& indices) {
    std::string palabras[4] = {"SELECT", "*", "FROM", "TABLA_PERSONA"};
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
    int n = 2; // Define el tamaño de la cuadrícula
    Controller2 controller2(n);
    controller2.run();
    return 0;
}

