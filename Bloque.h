#ifndef BLOQUE_H
#define BLOQUE_H
#include <vector>
#include <chrono>
class Bloque
{
  private:
    sf::RectangleShape shape;
    float x;
    float y;
    float vel;
    vector<float> arr; 
    vector<float> yInicio;
  public:
    Bloque();
    void gravity();
    void draw(sf::RenderWindow&);
    float getY();
};
class PoolBloques
{
  private:
    vector<Bloque*> bloques;
  public:
    PoolBloques();
    ~PoolBloques();
    void update();
};
#endif
