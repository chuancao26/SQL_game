#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <algorithm>
#include <random>

// Definición de las categorías de palabras
std::vector<std::string> palabrasTodas = {"SELECT", "*", "FROM", "producto", "nombre", 
    "descripcion", "precio", "orden", "id", "user_id", "amount", "date",
    "persona", "apellidos", "dni", "users", "name", "age", ">", "<", "<=",
    ">=", "!=", "=", "ORDER", "BY", "WHERE", "ASC", "DESC", "AND", "OR", "NOT", "1", "2", 
    "3", "4", "5", "6", "7", "8", "9", "0", ";"};

std::vector<std::string> palabrasReservadas = {"SELECT", "FROM", "WHERE", "ORDER", "BY", "AND", "OR", "NOT", "ASC", "DESC", "*"};
std::vector<std::string> comparaciones = {"=", "!=", "<", ">", "<=", ">="};
std::vector<std::string> numeros = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
std::vector<std::string> tabla1 = {"id", "name", "age", "users"};
std::vector<std::string> tabla2 = {"nombre", "id", "precio", "descripcion", "producto"};
std::vector<std::string> tabla3 = {"nombre", "id", "apellidos", "dni", "persona"};
std::vector<std::string> tabla4 = {"id", "user_id", "amount", "date", "orden"};

// Función para llenar el arreglo palabras
std::vector<std::string> llenarArregloPalabras() {
    std::vector<std::string> palabras;
    std::vector<std::string> tablaElegida;
    std::string nombreTabla;

    // Elegir una tabla al azar
    int tablaIndex = rand() % 4;
    switch (tablaIndex) {
        case 0: 
            tablaElegida = tabla1;
            nombreTabla = "tabla1.png";
            break;
        case 1: 
            tablaElegida = tabla2;
            nombreTabla = "tabla2.png";
            break;
        case 2: 
            tablaElegida = tabla3;
            nombreTabla = "tabla3.png";
            break;
        case 3: 
            tablaElegida = tabla4;
            nombreTabla = "tabla4.png";
            break;
    }

    // Agregar las palabras según las reglas
    palabras.push_back("SELECT");
    palabras.push_back("SELECT");
    palabras.push_back("FROM");
    palabras.push_back("FROM");
    palabras.push_back("WHERE");
    palabras.push_back("ORDER");
    palabras.push_back("BY");

    // Elegir 2 palabras adicionales de palabrasReservadas que no sean ASC ni DESC
    std::vector<std::string> palabrasReservadasRestantes = palabrasReservadas;
    palabrasReservadasRestantes.erase(std::remove(palabrasReservadasRestantes.begin(), palabrasReservadasRestantes.end(), "ASC"), palabrasReservadasRestantes.end());
    palabrasReservadasRestantes.erase(std::remove(palabrasReservadasRestantes.begin(), palabrasReservadasRestantes.end(), "DESC"), palabrasReservadasRestantes.end());
    std::random_shuffle(palabrasReservadasRestantes.begin(), palabrasReservadasRestantes.end());
    palabras.push_back(palabrasReservadasRestantes[0]);
    palabras.push_back(palabrasReservadasRestantes[1]);

    // Agregar aleatoriamente ASC o DESC
    palabras.push_back(rand() % 2 == 0 ? "ASC" : "DESC");

    // Agregar 1 palabra de comparaciones y 1 palabra de números
    palabras.push_back(comparaciones[rand() % comparaciones.size()]);
    palabras.push_back(numeros[rand() % numeros.size()]);

    // Agregar la última palabra de la tabla elegida dos veces
    palabras.push_back(tablaElegida.back());
    palabras.push_back(tablaElegida.back());

    // Elegir 2 palabras adicionales de la tabla elegida
    std::random_shuffle(tablaElegida.begin(), tablaElegida.end());
    palabras.push_back(tablaElegida[0]);
    palabras.push_back(tablaElegida[1]);

    return palabras;
}

// Clase Cuadrado

class Cuadrado {
public:
    Cuadrado(int id, const sf::Texture& texOriginal, const sf::Texture& texPalabra, sf::Vector2f originalPos, const std::string& palabra);
    void draw(sf::RenderWindow& window);
    void moveToTarget(sf::Vector2f targetPos);
    void returnToOriginal();
    bool contains(sf::Vector2f point);
    sf::Vector2f getPosition() const;
    bool isMoved() const;
    void updateOriginalPosition(sf::Vector2f newPos);
    void animateMovement(sf::Vector2f startPos, sf::Vector2f endPos);
    void incrementClickCount();
    int getClickCount() const;
    std::string getPalabra() const;
    
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
    int clickCount; // Click counter
    std::string palabra; // Associated word
};

Cuadrado::Cuadrado(int id, const sf::Texture& texOriginal, const sf::Texture& texPalabra, sf::Vector2f originalPos, const std::string& palabra)
    : id(id), originalPos(originalPos), currentPos(originalPos), moved(false), animating(false), animationDuration(0.5f), clickCount(0), palabra(palabra) {
    spriteOriginal.setTexture(texOriginal);
    spriteOriginal.setPosition(originalPos);
    spriteOriginal.setScale(125.0f / texOriginal.getSize().x, 100.0f / texOriginal.getSize().y); // Reduce the size to half

    spritePalabra.setTexture(texPalabra);
    spritePalabra.setPosition(originalPos); // Set initial position
    spritePalabra.setScale(75.0f / texPalabra.getSize().x, 75.0f / texPalabra.getSize().y); // Reduce the size to half
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

void Cuadrado::incrementClickCount() {
    clickCount++;
}

int Cuadrado::getClickCount() const {
    return clickCount;
}

std::string Cuadrado::getPalabra() const {
    return palabra;
}


vector<int> encontrarPosiciones(const vector<string>& a, vector<string>& b) {
    vector<int> numeros;

    for (const auto& palabra_a : a) {
        // Buscamos palabra_a en el vector b
        auto it = find(b.begin(), b.end(), palabra_a);
        
        if (it != b.end()) {
            // Obtenemos la posición de la palabra en b
            int posicion = distance(b.begin(), it);
            numeros.push_back(posicion);
        }
    }

    return numeros;
}


// Clase Controller2

class Controller2 {
public:
    Controller2(sf::RenderWindow& window, int n);
    void run();
    void render();

private:
    sf::RenderWindow& window;
    std::unique_ptr<sf::Texture> fondoOrdenTexture;
    std::unique_ptr<sf::Sprite> fondoOrdenSprite;
    std::vector<std::unique_ptr<sf::Texture>> imgOrdenTextures;
    std::vector<std::unique_ptr<sf::Texture>> imgPalabraTextures;
    std::unique_ptr<sf::Texture> tablaTexture;
    std::unique_ptr<sf::Sprite> tablaSprite;
    std::unique_ptr<sf::Texture> botonTexture1;
    std::unique_ptr<sf::Texture> botonTexture2;
    sf::Sprite botonSprite;
    sf::RectangleShape redSquare;
    std::vector<Cuadrado> cuadrados;

    int n;
    bool transitioning;
    std::vector<int> selectedIndices;

    void handleEvents();
    void organizeImages();
    void moveImage(int index);
    void returnImage(int index);
    void handleRedSquareClick();
    void resultadoPalabra(const std::vector<int>& indices);
    void randomizePositions();

    std::vector<std::string> llenarArregloPalabras();
};

Controller2::Controller2(sf::RenderWindow& window, int n)
    : window(window), n(n), transitioning(true), 
      fondoOrdenTexture(std::make_unique<sf::Texture>()),
      fondoOrdenSprite(std::make_unique<sf::Sprite>()),
      tablaTexture(std::make_unique<sf::Texture>()),
      tablaSprite(std::make_unique<sf::Sprite>()),
      botonTexture1(std::make_unique<sf::Texture>()), 
      botonTexture2(std::make_unique<sf::Texture>()) {

    fondoOrdenTexture->loadFromFile("img/fondoOrden.png");
    fondoOrdenSprite->setTexture(*fondoOrdenTexture);

    std::vector<int> positions(n * n);
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), std::mt19937{ std::random_device{}() });

    std::vector<int> imgIndices(n * n);
    std::iota(imgIndices.begin(), imgIndices.end(), 0);
    std::shuffle(imgIndices.begin(), imgIndices.end(), std::mt19937{ std::random_device{}() });

    std::vector<std::string> palabras = llenarArregloPalabras();

    vector<int> numeros = encontrarPosiciones(palabras, palabrasTodas);
    // Load imgPalabraTextures in the exact order of palabras
    for (int i = 0; i < n * n; ++i) {
        imgPalabraTextures.push_back(std::make_unique<sf::Texture>());
        imgPalabraTextures[i]->loadFromFile("img/imgPalabra" + std::to_string(numeros[i] + 1) + ".png");
    }

    for (int i = 0; i < n * n; ++i) {
        imgOrdenTextures.push_back(std::make_unique<sf::Texture>());
        imgOrdenTextures[i]->loadFromFile("img/imgOrden" + std::to_string(imgIndices[i] + 1) + ".png");
    }

    for (int i = 0; i < n * n; ++i) {
        float x = (positions[i] % n) * (window.getSize().x * 2 / 4 / n) + 40;
        float y = (positions[i] / n) * (window.getSize().y * 4 / 6 / n) + 40;
        sf::Vector2f originalPos(x, y);

        cuadrados.emplace_back(i, *imgOrdenTextures[i], *imgPalabraTextures[i], originalPos, palabras[i]);
    }

    tablaTexture->loadFromFile("img/tabla.png");
    tablaSprite->setTexture(*tablaTexture);
    tablaSprite->setPosition(window.getSize().x * 2 / 3, 100);

    botonTexture1->loadFromFile("img/boton1.png");
    botonTexture2->loadFromFile("img/boton2.png");
    botonSprite.setTexture(*botonTexture1);
    botonSprite.setScale(50.0f / botonTexture1->getSize().x, 50.0f / botonTexture1->getSize().y);
    botonSprite.setPosition(window.getSize().x * 2 / 3 - 25, 500);

    redSquare.setSize(sf::Vector2f(80, 80));
    redSquare.setFillColor(sf::Color::Transparent);
    redSquare.setPosition(window.getSize().x * 2 / 3 + 25, 500);
}

std::vector<std::string> Controller2::llenarArregloPalabras() {
    return ::llenarArregloPalabras();
}

// Resto de la implementación de la clase Controller2, sin cambios

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
            int countMoving = 0;
            for (int i = 0; i < n * n; ++i) {
                if (cuadrados[i].contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    cuadrados[i].incrementClickCount();
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
                botonSprite.setTexture(*botonTexture2); // Change to button 2 texture
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (redSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                botonSprite.setTexture(*botonTexture1); // Revert to button 1 texture
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
    botonSprite.setPosition(redSquare.getPosition().x, redSquare.getPosition().y); // Position the button to the right of the red square
    window.draw(botonSprite); // Draw the button with the current texture
    window.draw(redSquare);
}

void Controller2::moveImage(int index) {
    sf::Vector2f targetPos(100 + 100 * selectedIndices.size(), 600);
    cuadrados[index].moveToTarget(targetPos);
}

void Controller2::returnImage(int index) {
    cuadrados[index].returnToOriginal();
    selectedIndices.erase(std::remove(selectedIndices.begin(), selectedIndices.end(), index + 1), selectedIndices.end());
    // Reorganize moving images to fill gaps
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
    for (int indice : indices) {
        std::cout << cuadrados[indice - 1].getPalabra() << " ";
    }
    std::cout << std::endl;
}

void Controller2::render() {
    window.clear();
    organizeImages(); // Always organize and draw images
    window.display();
}


