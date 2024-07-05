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
    vector<Bloque*> bloques;
    int cantBloques;
    sf::Clock clock;
  public:
    Controller();
    void run();
    void renderizar();
};
#endif
