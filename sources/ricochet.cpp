#include "../headers/ricochet.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

ricochet::ricochet(const sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed)
: boing(texture, size, speed) {}

void ricochet::update(float deltatime)
{
    boing::update(deltatime);
    sf::Vector2f speedd = getSpeed();
    if ((getPosition().x - getBody().getSize().x / 2) < 250 || (getPosition().x + getBody().getSize().x / 2) > 1150 )
    {
        speedd.x = - speedd.x;
    }
    setSpeed(speedd);
}

std::unique_ptr<boing> ricochet::clone() const
{
    return std::make_unique<ricochet>(*this);
}


