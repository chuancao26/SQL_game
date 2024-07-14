#include "Controller.h"

Button::Button() : targetState(GameState::Menu) {}

Button::Button(sf::Texture& texture, float x, float y, GameState state)
    : targetState(state) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    bounds = sprite.getGlobalBounds();
}

Controller::Controller(): camarero(1280, 720, font), ganaste(false)
{
    font.loadFromFile("fonts/Arial.ttf");
    if (!playTexture.loadFromFile("img/menu/botonnivel1.jpg")) {
        // Manejar el error si la carga falla
        std::cerr << "Error cargando la textura botonplay.jpg" << std::endl;
    } else {
        playButton = Button(playTexture, 500.f, 300.f, GameState::Nivel1);
    }

    if (!tablasTexture.loadFromFile("img/menu/botonnivel2.jpg")) {
        // Manejar el error si la carga falla
        std::cerr << "Error cargando la textura botontablas.jpg" << std::endl;
    } else {
        tablasButton = Button(tablasTexture, 500.f, 420.f, GameState::Nivel2);
    }
    if (!salirTexture.loadFromFile("img/menu/botonsalir.jpg")) {
        // Manejar el error si la carga falla
        std::cerr << "Error cargando la textura botonsalir.jpg" << std::endl;
    } else {
        salirButton = Button(salirTexture, 500.f, 540.f, GameState::Salir);
    }
    level2 = std::make_unique<Controller2>(view.window,4);

}
void Controller::update()
{
    float deltaTime = clock.restart().asSeconds();

    switch (gameState) {
        case GameState::Menu: {
            sf::Vector2i mousePos = sf::Mouse::getPosition(view.window);
            sf::Vector2f mouseWorldPos = view.window.mapPixelToCoords(mousePos);

            // Verificar si se hace clic en el botón de jugar
            if (playButton.bounds.contains(mouseWorldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                gameState = playButton.targetState;
            }

            // Verificar si se hace clic en el botón de tablas
            if (tablasButton.bounds.contains(mouseWorldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                gameState = tablasButton.targetState;
            }
            if (salirButton.bounds.contains(mouseWorldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                gameState = salirButton.targetState;
            }
            break;
        }

        case GameState::Nivel1: {
            if(view.getRightButton())
            {
            player.moveRight(deltaTime);
            }
            if(view.getLeftButton())
            {
            player.moveLeft(deltaTime);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            camarero.setMapSelector("q");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camarero.setMapSelector("w");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            camarero.setMapSelector("e");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            camarero.setMapSelector("r");
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            camarero.spaceClean();
            view.update();
            camarero.update(deltaTime);
            camarero.colisiones(player.shape, analyzer);
            if (ganaste) {
                gameState = GameState::Won;  // Cambiar al estado de ganar si se cumple la condición
            }
            break;
        }
        case GameState::Nivel2: {
            level2->run();
            
            break;
        }
        case GameState::Tablas: {
            // Lógica del juego principal
            
            break;
        }

        case GameState::Won: {
            // Lógica de la pantalla de "ganaste"
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                gameState = GameState::Menu;  // Volver al menú cuando se presiona Enter
            }
            break;
        }

        case GameState::Salir: {
            view.window.close();  // Cerrar la ventana
            break;
        }

    }

    
}

void Controller::run()
{
  while(view.window.isOpen())
  {
    sf::Event event;
    while (view.window.pollEvent(event)) 
    {
      if (event.type == sf::Event::Closed)
	      view.window.close();
    }
    update();
    renderizar();
  }
}

void Controller::renderizar()
{
    view.window.clear();

    switch (gameState) {
        case GameState::Menu:
            view.setBackground(1);
            view.window.draw(playButton.sprite);
            view.window.draw(tablasButton.sprite);
            view.window.draw(salirButton.sprite);
            break;

        case GameState::Nivel1:
            
            view.window.clear();
            view.setBackground(2);
            player.draw(view.window);
            camarero.draw(view.window);
            view.window.display();
            break;
        case GameState::Nivel2:
            level2->render();
            break;
        case GameState::Tablas:
            
            break;

        case GameState::Won:
            view.setBackground(1);
            break;
    }

    view.window.display();
}
