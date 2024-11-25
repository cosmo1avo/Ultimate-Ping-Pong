#pragma once
#include "collider.hpp"

class wall
{
public:

    wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
    {
        body.setSize(size);
        body.setOrigin(size / 2.0f);
        body.setTexture(texture);
        body.setPosition(position);
    }

    wall(const wall& other)
    {
        body.setSize(other.body.getSize());
        body.setOrigin(other.body.getOrigin());
        body.setTexture(other.body.getTexture());
        body.setPosition(other.body.getPosition());
    }

    ~wall()
    {}

    void draw(sf::RenderWindow& window)
    {
        window.draw(body);
    }

    collider getcollider()
    {
        return collider(body);
    }

private:
    sf::RectangleShape body;
};
