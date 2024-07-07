#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Vista.cpp"
#include "Player.cpp"
#include "Bloque.cpp"
#include "Camarero.cpp"
class Controller
{
  private:
    Vista view;
    Player player;
    Camarero camarero;

  public:
    Controller();
    void run();
    void renderizar();
    void update();
};
#endif
