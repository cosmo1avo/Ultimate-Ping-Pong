#include "../headers/hockey.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

hockey::hockey(const sf::Texture* texture, sf::Vector2f size, sf::Vector2f speed)
: boing(texture, size, speed), base(0.0f) {}

void hockey::update(float deltatime)
{
    boing::update(deltatime);
    sf::Vector2f speedd = getSpeed();
    if(((getBody().getPosition().y < 839.0f &&  getBody().getPosition().y > 830.0f) || (getBody().getPosition().y < 170.0f &&  getBody().getPosition().y > 161.0f)) && speedd.y < 1000.0f)
    {
        base = speedd.y;
        speedd.y = factor * speedd.y;
    }

    if(getBody().getPosition().y < 820.0f && getBody().getPosition().y > 180.0f)
    {
        speedd.y = speedd.y - base/20.0f;
    }

    setSpeed(speedd);
}

std::unique_ptr<boing> hockey::clone() const
{
    return std::make_unique<hockey>(*this);
}

void hockey::drawShape(sf::RenderWindow& window) const
{
    boing::drawShape(window);
}

