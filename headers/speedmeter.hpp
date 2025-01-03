#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class speedmeter {
public:
    speedmeter();

    void setX(const float _x);

    void setY(const float _y);

    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape _speedmeter;
};