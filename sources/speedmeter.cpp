#include "../headers/speedmeter.hpp"
#include <SFML/Graphics.hpp>

speedmeter::speedmeter() {
    _speedmeter.setSize(sf::Vector2f(20, 5));
    _speedmeter.setFillColor(sf::Color::Magenta);
    _speedmeter.setOrigin(0, 2.5);
}

void speedmeter::setX(const float _x) {
    _speedmeter.setPosition(_x,_speedmeter.getPosition().y);
}

void speedmeter::setY(const float _y) {
    _speedmeter.setPosition(_speedmeter.getPosition().x,_y);
}

sf::Vector2f speedmeter::getPosition() const {
    return _speedmeter.getPosition();
}

void speedmeter::draw(sf::RenderWindow& window) {
    window.draw(_speedmeter);
}

