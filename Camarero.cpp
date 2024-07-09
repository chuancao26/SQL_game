#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY): limiteX(limiteX), limiteY(limiteY),spawnTime(0), srand(static_cast<unsigned>(std::time(nullptr)))
{
}
void Camarero::update(float& deltaTime)
{
  spawn(deltaTime);
  movement();
  colisiones();
}
void Camarero::spawn(float& deltaTime)
{
  spawnTime += deltaTime;
  if(spawnTime == 1.0f)
  {
    float x = static_cast<float>(std::rand() % limiteX); 
    Bloque bloque(x, -50);
    bloques.push_back(bloque);
    spawnTime = 0;
  }
}
void Camarero::movement()
{
  for(auto it = bloques.begin(); it != bloques.end();)
  {
    it -> gravity();
    if(it -> getY() > limiteY)
    {
      it = bloque.erase(it);
    }
    else
    {
      ++i;
    }
  }
}
void Camarero::draw(sf::RenderWindow& window)
{
  for(auto bloque : bloques)
  {
    bloque.draw(window);
  }
}
void Camarero::colisiones(sf::RectangleShape& player)
{
  for(auto bloque : bloques)
  {
    if(player.getLocalBounds().intersects(bloque.shape.getLocalBounds()))
      cout << 1 << endl;
  }
}
