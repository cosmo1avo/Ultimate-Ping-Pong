#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class arrow {
public:
    arrow();

    void setPosition(const sf::Vector2f& position);

    void setRotation(float angle);

    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape _arrow;
};
