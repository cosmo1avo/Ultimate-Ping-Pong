#pragma once
#include "collider.hpp"

class player
{
public:
    player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed, sf::Vector2f startPosition, int nr)
        : animation1(texture, imagecount, switchtime), nr(nr), pos_x(0), row(0), faceright(true), blocat(false)
    {
        this->speed = speed;

        body.setSize(sf::Vector2f(100.0f, 100.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(startPosition);
        body.setTexture(texture);
    }

    void update(float deltatime)
    {
        movement.x = 0.0f;
        if(!blocat)
        {
            if (nr == 1)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    movement.x -= speed * deltatime;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    movement.x += speed * deltatime;
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    movement.x -= speed * deltatime;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    movement.x += speed * deltatime;
            }

            if (movement.x == 0.0f)
                row = 0;
            else
            {
                row = 1;
                faceright = (movement.x > 0.0f);
            }
            pos_x += movement.x;
            body.move(movement);
        }
        animation1.update(row, deltatime, faceright);
        body.setTextureRect(animation1.getuvrect());
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

    void setPosition(float x)
    {
        body.setPosition(x, body.getPosition().y);
        this->pos_x = x;
    }

    sf::Vector2f getPosition() const {
        return body.getPosition();
    }

    void blocaj(bool b)
    {
        blocat = b;
    }

    [[nodiscard]] float getPosX() const
    {
        return pos_x;
    }

    friend std::ostream& operator<<(std::ostream& stream, const player& _player)
    {
        stream << "position: " << _player.getPosX() << "\n";
        stream << "faceright: " << _player.faceright << "\n";
        stream << "row: " << _player.row << "\n";
        stream << "nr: " << _player.nr;
        return stream;
    }

private:
    sf::RectangleShape body;
    animation animation1;
    int nr, row;
    float speed, pos_x;
    bool faceright, blocat;
    sf::Vector2f movement{ 0.0f, 0.0f };
};
