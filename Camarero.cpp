#include "Camarero.h" 
Camarero::Camarero(int limiteX, int limiteY, const sf::Font& font): limiteX(limiteX), limiteY(limiteY),spawnTime(0), font(font), query(""), status(false), printStatus(false), mapSelector("q"), statusSelector(true),  text1("Press Q to show clauses", 700, 350, font), text2("Press W to show operators", 700, 370 , font), text3("Press E to show identificadores", 700, 390, font), text4("Press R to show numeros", 700, 410, font), text5("Presiona Espacio para limpiar", 700, 430, font)
{
  std::random_device rd;
  rng = std::mt19937(rd());
  words["q"] = {"SELECT", "FROM", "WHERE", "ORDER", "BY", "AND", "OR", "NOT", "ASC", "DESC"};
  words["w"] = {"=", "!=", "<", ">", "<=", ">="};
  words["e"] = {"*",",","producto", "nombre", "descripcion", "precio", "id","user_id",";", "amount", "date", "edad", "apellidos", "dni"};
  words["r"] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "0", ";"};
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}
void Camarero::instruccions(sf::RenderWindow& window)
{
  text1.draw(window);
  text2.draw(window);
  text3.draw(window);
  text4.draw(window);
  text5.draw(window);
}
void Camarero::update(float& deltaTime)
{
  spawn(deltaTime);
  movement(deltaTime);

  statusTime += deltaTime;
  if (statusTime >= 4.0f)
  {
    printStatus = false;
    statusTime = 0;
  }
  timeSelector += deltaTime;
  if(timeSelector >= 2.0f)
  {
    statusSelector = true;
  }
}
void Camarero::spawn(float& deltaTime)
{
  spawnTime += deltaTime;
  if(spawnTime >= 0.5f)
  {
    float x = static_cast<float>(std::rand() % (limiteX - 700)); 
    std::uniform_int_distribution<> dist(0, words[mapSelector].size() - 1);
    int select_word = dist(rng);
    Bloque bloque(x, -50, words[mapSelector][select_word], font);
    bloques.push_back(bloque);
    spawnTime = 0;
  }

}
void Camarero::dropWord()
{
  for(auto it = words["q"].begin(); it != words["q"].end();)
  {
    if(query.find(*it) != std::string::npos && it -> size() >= 4)
    {
      it = words["q"].erase(it);
    }
    ++it;
  }
}
void Camarero::resetWords()
{
  words["q"] = {"SELECT", "FROM", "WHERE", "ORDER", "BY", "AND", "OR", "NOT", "ASC", "DESC"};
  words["w"] = {"=", "!=", "<", ">", "<=", ">="};
  words["e"] = {"*",",","producto", "nombre", "descripcion", "precio", "pais", ";"};
  words["r"] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "0", ";"};
}
void Camarero::movement(float& deltaTime)
{
  for(auto it = bloques.begin(); it != bloques.end();)
  {
    it -> gravity(deltaTime);
    if(it -> getY() > limiteY - 100)
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

  instruccions(window);
  // Query
  sf::Text capturedText;
  capturedText.setFont(font);
  capturedText.setString(query);
  capturedText.setCharacterSize(20);
  capturedText.setFillColor(sf::Color::White);
  capturedText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  capturedText.setOutlineColor(sf::Color::Black);
  capturedText.setOutlineThickness(2);
  capturedText.setPosition(40, 690);
  window.draw(capturedText);

  if(status && printStatus)
  {
  sf::Text statusWord;
  statusWord.setFont(font);
  statusWord.setString("Buen Trabajo!!!");
  statusWord.setCharacterSize(20);
  statusWord.setFillColor(sf::Color::White);
  statusWord.setStyle(sf::Text::Bold | sf::Text::Underlined);
  statusWord.setOutlineColor(sf::Color::Black);
  statusWord.setOutlineThickness(2);
  statusWord.setPosition(700, 200);
  window.draw(statusWord);
  }

  if(!status && printStatus)
  {
  sf::Text statusWord;
  statusWord.setFont(font);
  statusWord.setString(errorMessage);
  statusWord.setCharacterSize(20);
  statusWord.setFillColor(sf::Color::White);
  statusWord.setStyle(sf::Text::Bold | sf::Text::Underlined);
  statusWord.setOutlineColor(sf::Color::Black);
  statusWord.setOutlineThickness(2);
  statusWord.setPosition(700, 200);
  window.draw(statusWord);
  }
}
void Camarero::colisiones(sf::Sprite & player, Analyzer analyzer)
{
  for(auto it = bloques.begin(); it != bloques.end();)
  {
    if(player.getGlobalBounds().intersects(it -> text.getGlobalBounds()))
    {
      query += it -> getWord() + " ";
      if(it -> getWord() == ";")
      {
	resetWords();
	printStatus = true;
	if(analyzer.getStatus(query))
	{
	  status = true;
	}
	else
	{
	  status = false;
	  errorMessage = analyzer.getMessage();
	}
	query = "";
      }
      it = bloques.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
void Camarero::setMapSelector(string selector)
{
  if (statusSelector)
  {
    mapSelector = selector;
    statusSelector = false;
    timeSelector = 0;
  }
}
void Camarero::spaceClean()
{
  query = "";
  resetWords();
}
