#include "../headers/basic.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

basic::basic(const sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed)
    : boing(texture, size, speed) {}

void basic::update(float deltatime)
{
    boing::update(deltatime);
    sf::Vector2f speedd = getSpeed();
    setSpeed(speedd);
}

std::unique_ptr<boing> basic::clone() const
{
    return std::make_unique<basic>(*this);
}