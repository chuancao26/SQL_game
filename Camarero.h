#ifndef CAMARERO_H
#define CAMARERO_H
class Camarero
{
  private:
    vector<string> words;
    int limiteX;
    int limiteY;
    float spawnTime;
    void spawn(float&);
    void movement(float&);
    const sf::Font& font;

  public:
    vector<Bloque> bloques;
    string query;
    Camarero(int, int, const sf::Font&);
    void draw(sf::RenderWindow&);
    void update(float&);
    void colisiones(sf::RectangleShape&, Analyzer);
};
#endif
