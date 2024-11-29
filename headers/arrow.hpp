#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class arrow {
public:
    arrow() {
        _arrow.setSize(sf::Vector2f(100, 5));
        _arrow.setFillColor(sf::Color::Red);
        _arrow.setOrigin(0, 2.5);
    }

    void setPosition(const sf::Vector2f& position) {
        _arrow.setPosition(position);
    }

    void setRotation(float angle) {
        _arrow.setRotation(angle);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(_arrow);
    }


private:
    sf::RectangleShape _arrow;
};
