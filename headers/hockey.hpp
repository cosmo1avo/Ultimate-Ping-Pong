#pragma once
#include "boing.hpp"
#include <SFML/Graphics.hpp>

class hockey : public boing
{
public:
    hockey(const sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed);

    void update(float deltatime) override;

    std::unique_ptr<boing> clone() const override;

private:
    float base;
    float factor = rand() %3 + 2;
};
