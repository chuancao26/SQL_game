#ifndef CAMARERO_H
#define CAMARERO_H
class Camarero
{
  private:
    vector<string> words;
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

  public:
    vector<Bloque> bloques;
    string query;
    Camarero(int, int, const sf::Font&);
    void draw(sf::RenderWindow&);
    void update(float&);
    void colisiones(sf::RectangleShape&, Analyzer);
};
#endif
