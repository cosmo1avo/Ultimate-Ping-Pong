#pragma once
#include "collider.hpp"

class wall
{
public:

    wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f _position)
    {
        position = _position;
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

    wall& operator=(const wall& other)
    {
        if (this == &other) 
            return *this;

        body.setSize(other.body.getSize());
        body.setOrigin(other.body.getOrigin());
        body.setTexture(other.body.getTexture());
        body.setPosition(other.body.getPosition());

        return *this;
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

    friend std::ostream& operator<<(std::ostream& stream, const wall& _wall)
    {
        stream << "wall position: " <<" X:" <<  _wall.position.x << " Y:" << _wall.position.y;
        return stream;
    }


private:
    sf::RectangleShape body;
    sf::Vector2f position;
};
