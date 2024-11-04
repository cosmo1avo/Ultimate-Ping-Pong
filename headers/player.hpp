#pragma once
#include "collider.hpp"
#include <SFML\Graphics.hpp>

class player
{
public:
    player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime,float speed):
       animation(texture, imagecount, switchtime)
    {
        this->speed = speed;
        row = 0;
        faceright = true;

        body.setSize(sf::Vector2f(100.0f, 100.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(400.0f, 400.0f);
        body.setTexture(texture);
    }
    void update(float deltatime)
    {
        sf::Vector2f movement(0.0f, 0.0f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= speed * deltatime;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += speed * deltatime;
        if(movement.x == 0.0f)
            row = 0;
        else
        {
            row =1;
            if(movement.x>0.0f)
                faceright = true;
            else
                faceright = false;
        }
        animation.update(row,deltatime,faceright);
        body.setTextureRect(animation.getuvrect());
        body.move(movement);
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
        body.move(dx,dy);
    }
private:
    sf::RectangleShape body;
    animation animation;
    unsigned int row;
    float speed;
    bool faceright;

};