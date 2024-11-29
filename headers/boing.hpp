#pragma once
#include "collider.hpp"

class boing
{
public:
    boing(sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed)
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
        movement.x = 0.0f;
        movement.y = 0.0f;
        if (!glue)
        {
            movement.x = speed.x * deltatime;
            movement.y = speed.y * deltatime;
            x += movement.x;
            y += movement.y;
            body.move(movement);
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

    void setPosition(float x, float y)
    {
        body.setPosition(x, y);
        this->x = x;
        this->y = y;
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
