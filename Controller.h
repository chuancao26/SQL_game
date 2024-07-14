#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Analyzers.cpp"
#include "Vista.cpp"
#include "Player.cpp"
#include "Bloque.cpp"
#include "Camarero.cpp"
#include "Controller2.cpp"

enum class GameState {
    Menu,
    Nivel1,
    Nivel2,
    Tablas,
    Won,
    Salir
};

struct Button {
    sf::Sprite sprite;
    sf::FloatRect bounds;
    GameState targetState;

    Button();
    // Constructor para inicializar el botón con su textura y área
    Button(sf::Texture& texture, float x, float y, GameState state);
};

GameState gameState = GameState::Menu;  // Estado inicial: Menú

class Controller
{
  private:
    Vista view;
    Player player;
    Camarero camarero;
    bool ganaste;
    Button playButton;
    Button tablasButton;
    Button salirButton;
    sf::Texture playTexture;
    sf::Texture tablasTexture;
    sf::Texture salirTexture;
    std::unique_ptr<Controller2> level2;

    sf::Clock clock;
    sf::Font font;

    Analyzer analyzer;
  public:
    Controller();
    void run();
    void renderizar();
    void update();
};
#endif
