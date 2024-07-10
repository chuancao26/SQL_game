#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY, const sf::Font& font): limiteX(limiteX), limiteY(limiteY),spawnTime(0), font(font), query("")
{
  words = {
    // Keywords
    "SELECT", "FROM", "WHERE", "ORDER", "BY", "AND", "OR", "NOT",

    // Operators
    "=", "!=", "<", ">", "<=", ">=",

    // Functions
    "*",

    // Identifiers (representativos)
    "personas", "nombre", "edad", "ciudad", "pais",

    // Literals (ejemplos)
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "0",

    // Order by modifiers
    "ASC", "DESC"
  };

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
  if(spawnTime >= 1.0f)
  {
    float x = static_cast<float>(std::rand() % (limiteX - 700)); 
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

  // words
  sf::Text capturedText;
  capturedText.setFont(font);
  capturedText.setString(query);
  capturedText.setCharacterSize(12);
  capturedText.setFillColor(sf::Color::Yellow);
  capturedText.setPosition(700, 100);
  window.draw(capturedText);

}
void Camarero::colisiones(sf::RectangleShape& player)
{
  for(auto it = bloques.begin(); it != bloques.end();)
  {
    if(player.getGlobalBounds().intersects(it -> text.getGlobalBounds()))
    {
      query += it -> getWord();
      query += " ";
      it = bloques.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
