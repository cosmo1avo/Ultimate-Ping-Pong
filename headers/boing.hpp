#pragma once
#include "collider.hpp"

class boing
{
public:
    boing(sf::Texture* texture, sf::Vector2f size,sf::Vector2f speed)
        : x(0), y(0), glue(false)
    {
        this->speed = speed;
        body.setSize(size);
        body.setOrigin(size / 2.0f);
        body.setTexture(texture);
        body.setPosition(400, 400);
    }

    void update(float deltatime)
    {
        sf::Vector2f local_movement{ 0.0f, 0.0f };
        if (!glue)
        {
            local_movement.x = speed.x * deltatime;
            local_movement.y = speed.y * deltatime;
            x += local_movement.x;
            y += local_movement.y;
            body.move(local_movement);
        }
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(body);
    }

    collider getcollider()
    {
        return collider(body);
    }

    void move(float dx, float dy)
    {
        body.move(dx, dy);
    }

    void setPosition(float _x, float _y)
    {
        body.setPosition(_x, _y);
        this->x = _x;
        this->y = _y;
    }

    sf::Vector2f getPosition() const
    {
        return body.getPosition();
    }

    void setVelocity(sf::Vector2f v)
    {
        speed = v;
    }

    void attach()
    {
        glue = true;
        speed = { 0.0f, 0.0f };
    }

    void deglue()
    {
        glue = false;
    }

private:
    sf::RectangleShape body;
    sf::Vector2f movement{ 0.0f, 0.0f };
    float x, y;
    sf::Vector2f speed{ 0.0f, 0.0f };
    bool glue;
};
