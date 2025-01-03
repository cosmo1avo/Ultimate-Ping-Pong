#include "../headers/decel.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

decel::decel(sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed)
    : boing(texture, size, speed) {}

void decel::update(float deltatime)
{
    boing::update(deltatime);
    sf::Vector2f speedd = getSpeed();
    if((getBody().getPosition().y < 839.0f &&  getBody().getPosition().y > 830.0f) || (getBody().getPosition().y < 170.0f &&  getBody().getPosition().y > 161.0f))
        base = speedd.x;
    speedd.x = speedd.x - base / 50.0f;
    setSpeed(speedd);
}

std::unique_ptr<boing> decel::clone() const
{
    return std::make_unique<decel>(*this);
}