#pragma once
#include "boing.hpp"
#include <SFML/Graphics.hpp>
#include "collider.hpp"

class basic : public boing
{
public:
    basic(const sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed);

    void update(float deltatime) override;

    std::unique_ptr<boing> clone() const override;

    void drawShape(sf::RenderWindow& window) const override;

};