#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY): cantCol(4), cantFil(3), bloques(3, vector<Bloques*>(4)), limiteX(limiteX), limiteY(limiteY), gen(rd()), d(0.3)
{
  for(int i = 0; i < cantFil; i++)
  {
    for(int j = 0; j < cantCol; j++)
    {
      bloques[i][j] = new Bloque(-limiteX / cantCol, -limiteY / cantFil);
    }
  }
}
void Camarero::draw()
{
  for(int i = 0; i < cantFil; i++)
  {
    for(int j = 0; j < cantCol; j++)
    {
      bloques[i][j].draw
    }
  }
}
