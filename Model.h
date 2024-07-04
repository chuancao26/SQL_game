#ifndef MODEL_H
#define MODEL_H
#include "Player.h"
class Model
{
  private:
    Player player;
    bool rightB;
    bool leftB;
  public:
    Model();
    void setRightB(bool);
    void setLeftB(bool);
    void update();
}
#endif
