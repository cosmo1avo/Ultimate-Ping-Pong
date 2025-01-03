#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class collider
{
public:
    explicit collider(sf::RectangleShape& body);

    bool check_collision(collider other,float push);

    void movef(float dx, float dy);

    sf::Vector2f getposition();

    sf::Vector2f gethalfsize();


private:
    sf::RectangleShape body;
};