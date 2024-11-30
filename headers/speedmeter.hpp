#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class speedmeter {
public:
    speedmeter() {
        _speedmeter.setSize(sf::Vector2f(20, 5));
        _speedmeter.setFillColor(sf::Color::Magenta);
        _speedmeter.setOrigin(0, 2.5);
    }

    void setX(const float _x) {
        _speedmeter.setPosition(_x,_speedmeter.getPosition().y);
    }

    void setY(const float _y) {
        _speedmeter.setPosition(_speedmeter.getPosition().x,_y);
    }

    sf::Vector2f getPosition() const {
        return _speedmeter.getPosition();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(_speedmeter);
    }


private:
    sf::RectangleShape _speedmeter;
};