#pragma once
#include "collider.hpp"
#include <memory>

class boing
{
public:
    boing(const sf::Texture* texture, sf::Vector2f size,sf::Vector2f speed);

    virtual ~boing() = default;

    virtual void update(float deltatime) = 0;

    virtual std::unique_ptr<boing> clone() const = 0;

    void draw(sf::RenderWindow& window) const;

    virtual void drawShape(sf::RenderWindow& window) const;

    collider getcollider();

    void move(float dx, float dy);

    void setPosition(float _x, float _y);

    sf::Vector2f getPosition() const;

    void setVelocity(sf::Vector2f v);

    void attach();

    void deglue();

    const sf::RectangleShape& getBody() const;

    sf::Vector2f getSpeed() const;

    void setSpeed(const sf::Vector2f& newSpeed);

private:
    sf::RectangleShape body;
    sf::Vector2f movement{ 0.0f, 0.0f };
    float x, y;
    sf::Vector2f speed{ 0.0f, 0.0f };
    bool glue;
};
