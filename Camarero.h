#ifndef CAMARERO_H
#define CAMARERO_H
#include <unordered_map>
class TextDisplay
{
private:
  sf::Text text;

public:
  TextDisplay(string content, float posX, float posY, const sf::Font& font)
  {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setPosition(posX, posY);
  }
  void draw(sf::RenderWindow& window)
  {
    window.draw(text);
  }
};
class Tables
{
  public:
    sf::Texture texture;
    sf::Sprite shape;
    Tables(float x, float y, string path)
    {
      texture.loadFromFile("img/Camarero/" + path);
      shape.setTexture(texture);
      shape.setPosition(x, y);
      shape.setScale(0.4f, 0.4f);
    }
    void draw(sf::RenderWindow& window)
    {
      window.draw(shape);
    }
};
class Camarero
{
  private:
    std::unordered_map<string, vector<string>> words;
    string mapSelector;
    float timeSelector;
    bool statusSelector;

    int limiteX;
    int limiteY;
    float spawnTime;
    const sf::Font& font;
    std::mt19937 rng;

    bool status;
    bool printStatus;
    float statusTime;
    string errorMessage;

    void spawn(float&);
    void movement(float&);
    void dropWord();
    void resetWords();

    void instruccions(sf::RenderWindow&);
    TextDisplay text1;
    TextDisplay text2;
    TextDisplay text3;
    TextDisplay text4;
    TextDisplay text5;
    Tables tableUser;
    Tables tablePersona;
    Tables tableProducto;
    Tables tableOrden;

  public:
    vector<Bloque> bloques;
    string query;
    Camarero(int, int, const sf::Font&);
    void draw(sf::RenderWindow&);
    void update(float&);
    void colisiones(sf::Sprite&, Analyzer);
    void setMapSelector(string);
    void spaceClean();
};
#endif
