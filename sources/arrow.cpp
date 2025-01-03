#include "../headers/arrow.hpp"
#include <SFML/Graphics.hpp>

arrow::arrow() {
    _arrow.setSize(sf::Vector2f(100, 5));
    _arrow.setFillColor(sf::Color::Red);
    _arrow.setOrigin(0, 2.5);
}

void arrow::setPosition(const sf::Vector2f& position) {
    _arrow.setPosition(position);
}

void arrow::setRotation(float angle) {
    _arrow.setRotation(angle);
}

void arrow::draw(sf::RenderWindow& window) {
    window.draw(_arrow);
}


