#pragma once
#include "collider.hpp"

class wall
{
public:
    wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f _position);

    wall(const wall& other);

    wall& operator=(const wall& other);

    ~wall();

    void draw(sf::RenderWindow& window);

    void settextoffset(int x, int y, int width, int height);


    collider getcollider();

    friend std::ostream& operator<<(std::ostream& stream, const wall& _wall);

private:
    sf::RectangleShape body;
    sf::Vector2f position;
};
