#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();

protected:
    void applyTexture(const std::string& textureFile);

    sf::RectangleShape shape;
};