#include "../headers/player.hpp"


player::player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed, sf::Vector2f startPosition, int nr)
        : animation1(texture, imagecount, switchtime), nr(nr), x_position(0)
    {
        this->speed = speed;
        row = 0;
        faceright = true;

        body.setSize(sf::Vector2f(100.0f, 100.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(startPosition);
        body.setTexture(texture);
    }

    void player::update(float deltatime)
    {
        movement.x = 0.0f;
        if (!blocat)
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
            x_position += movement.x;
            body.move(movement);
        }
        animation1.update(row, deltatime, faceright);
        body.setTextureRect(animation1.getuvrect());
    }

    void player::draw(sf::RenderWindow& window)
    {
        window.draw(body);
    }

    collider player::getcollider()
    {
        return collider(body);
    }

    void player::move(float dx, float dy)
    {
        body.move(dx, dy);
    }

    void player::setPosition(float _x)
    {
        body.setPosition(_x, body.getPosition().y);
        this->x_position = _x;
    }

    sf::Vector2f player::getPlayerPosition() const {
        return body.getPosition();
    }

    void player::blocaj(bool b)
    {
        blocat = b;
    }

    [[nodiscard]] float player::getx() const
    {
        return x_position;
    }

    std::ostream& operator<<(std::ostream& stream, const player& _player)
    {
        stream << "position: " << _player.getx() << "\n";
        stream << "faceright: " << _player.faceright << "\n";
        stream << "row: " << _player.row << "\n";
        stream << "nr: " << _player.nr;
        return stream;
    }