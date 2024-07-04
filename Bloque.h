#ifndef BLOQUE_H
#define BLOQUE_H
class Bloque
{
  private:
    sf::RectangleShape shape;
    float x;
    float y;
    float vel;
  public:
    Bloque();
    void gravity();
    void draw(sf::RenderWindow&);
};
