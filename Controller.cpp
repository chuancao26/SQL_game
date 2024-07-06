#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Vista.cpp"
#include "Player.cpp"
#include "Bloque.cpp"

class Controller
{
  private:
    Vista view;
    Player player;
    std::vector<Bloque*> bloques;
    int cantBloques;
    sf::Clock clock;
    sf::RenderWindow& window;

  public:
    Controller(sf::RenderWindow& window);
    void run();
    void renderizar();
};

#endif

#include "Controller.h"

Controller::Controller(sf::RenderWindow& window) 
    : cantBloques(10), bloques(10), window(window) {
    for (int i = 0; i < cantBloques; i++) {
        bloques[i] = new Bloque();
    }
}

void Controller::run() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    view.update();
    if (view.getRightButton()) {
        player.moveRight();
    }
    if (view.getLeftButton()) {
        player.moveLeft();
    }
    for (int i = 0; i < cantBloques; i++) {
        bloques[i]->gravity();
    }
    renderizar();
}

void Controller::renderizar() {
    window.clear();
    player.draw(window);
    for (int i = 0; i < cantBloques; i++) {
        bloques[i]->draw(window);
    }
    window.display();
}

#include "Vista.h"

Vista::Vista() : window(sf::VideoMode(1280, 720), "SQL") {
    window.setFramerateLimit(60);
}

void Vista::update() {
    rightButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    leftButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool Vista::getRightButton() {
    return rightButton;
}

bool Vista::getLeftButton() {
    return leftButton;
}
