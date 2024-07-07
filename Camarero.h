#ifndef CAMARERO_H
#define CAMARERO_H
class Camarero
{
  private:
    vector<vector<Bloque*>> bloques;
    int cantFil;
    int cantCol;
    int limiteX;
    int limiteY;
  public:
    Camarero(int, int);
    void draw(sf::RenderWindow&);
    void update();
};
#endif
