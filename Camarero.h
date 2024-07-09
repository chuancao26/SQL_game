#ifndef CAMARERO_H
#define CAMARERO_H
class Camarero
{
  private:
    vector<Bloque> bloques;
    int limiteX;
    int limiteY;
    float spawnTime;
    std::srand;
    void spawn(float&);
    void movement()
  public:
    Camarero(int, int);
    void draw(sf::RenderWindow&);
    void update(float&);
};
#endif
