#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY): cantCol(4), cantFil(3), bloques(3, vector<Bloque*>(4)), limiteX(limiteX), limiteY(limiteY)
{
  for(int i = 0; i < cantFil; i++)
  {
    for(int j = 0; j < cantCol; j++)
    {
      bloques[i][j] = new Bloque((j + 0.1) * 1.2 * (limiteX / cantCol), i * -limiteY / cantFil);
    }
  }
  cout << bloques[0].size() << endl;
}
void Camarero::update()
{
  for(int i = 0; i < cantFil; i++)
  {
    for(int j = 0; j < cantCol; j++)
    {
      bloques[i][j] -> gravity();
    }
  }
}
void Camarero::draw(sf::RenderWindow& window)
{
  for(int i = 0; i < cantFil; i++)
  {
    for(int j = 0; j < cantCol; j++)
    {
      bloques[i][j] -> draw(window);
    }
  }
}
