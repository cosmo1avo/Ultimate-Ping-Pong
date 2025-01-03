#pragma once
#include "collider.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.hpp"

class player
{
public:
    player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime, float speed, sf::Vector2f startPosition, int nr);


    void update(float deltatime);

    void draw(sf::RenderWindow& window);

    collider getcollider();

    void move(float dx, float dy);

    void setPosition(float _x);

    sf::Vector2f getPlayerPosition() const;

    void blocaj(bool b);

    [[nodiscard]] float getx() const;

    friend std::ostream& operator<<(std::ostream& stream, const player& _player);
private:
    sf::RectangleShape body;
    animation animation1;
    int nr, row;
    float speed, x_position;
    bool faceright, blocat;
    sf::Vector2f movement{ 0.0f, 0.0f };
};
