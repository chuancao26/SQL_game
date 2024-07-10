#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY, const sf::Font& font): limiteX(limiteX), limiteY(limiteY),spawnTime(0), font(font)//, srand(static_cast<unsigned>(std::time(nullptr)))
{
  words = {"SELECT", "FROM", "WHERE", "AND", "OR", "NOT"};
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}
void Camarero::update(float& deltaTime)
{
  spawn(deltaTime);
  movement(deltaTime);
}
void Camarero::spawn(float& deltaTime)
{
  spawnTime += deltaTime;
  cout << spawnTime << endl;
  if(spawnTime >= 1.0f)
  {
    float x = static_cast<float>(std::rand() % limiteX); 
    int select_word = static_cast<int>(std::rand() % words.size());
    Bloque bloque(x, -50, words[select_word], font);
    bloques.push_back(bloque);
    spawnTime = 0;
  }
}
void Camarero::movement(float& deltaTime)
{
  for(auto it = bloques.begin(); it != bloques.end();)
  {
    it -> gravity(deltaTime);
    if(it -> getY() > limiteY)
    {
      it = bloques.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
void Camarero::draw(sf::RenderWindow& window)
{
  for(int i = 0; i < bloques.size(); i++)
  {
    bloques[i].draw(window);
  }

}
//void Camarero::colisiones(sf::RectangleShape& player)
//{
//  for(auto bloque : bloques)
//  {
//    if(player.getGlobalBounds().intersects(bloque.text.getGlobalBounds()))
//      cout << 1 << endl;
//  }
//}
