#include "Bloque.h"
Bloque::Bloque(): vel(0.1f)
{

}
void Bloque::gravity()
{
  y += vel;
}
