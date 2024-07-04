#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Vista.cpp"
#include "Player.cpp"
class Controller
{
  private:
    Vista view;
    Player player;
  public:
    Controller();
    void run();
    void renderizar();
};
#endif
