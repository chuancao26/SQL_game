#ifndef CAMARERO_H
#define CAMARERO_H
class Camarero {
public:
    Camarero(int limiteX, int limiteY, const sf::Font& font);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void colisiones(sf::RectangleShape& player);

private:
    void spawn(float deltaTime);
    void movement(float deltaTime);

    int limiteX;
    int limiteY;
    float spawnTime;
    std::vector<std::string> words;
    std::vector<Bloque> bloques;
    const sf::Font& font;
};

#endif // CAMARERO_H

