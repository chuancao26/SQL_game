#include "Model.h"
void Model::setRightB(bool x)
{
  rightB = x;
}
void Model::setLeftB(bool x)
{
  leftB = x;
}
void Model::update()
{
  if(rightB)
  {
    player.moveRight();
  }
  if(leftB)
  {
    player.moveLeft();
  }
  player.draw();
}
