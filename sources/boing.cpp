#include "../headers/boing.hpp"
#include <SFML/Graphics.hpp>

boing::boing(sf::Texture* texture, sf::Vector2f size,sf::Vector2f speed)
: x(0), y(0), glue(false)
 {
     this->speed = speed;
     body.setSize(size);
     body.setOrigin(size / 2.0f);
     body.setTexture(texture);
     body.setPosition(400, 400);
 }

void boing::update(float deltatime)
 {
     sf::Vector2f local_movement{ 0.0f, 0.0f };
     if (!glue)
     {
         local_movement.x = speed.x * deltatime;
         local_movement.y = speed.y * deltatime;
         x += local_movement.x;
         y += local_movement.y;
         body.move(local_movement);
     }
 }

void boing::draw(sf::RenderWindow& window)
 {
     window.draw(body);
 }

collider boing::getcollider()
 {
     return collider(body);
 }

void boing::move(float dx, float dy)
 {
     body.move(dx, dy);
 }

void boing::setPosition(float _x, float _y)
 {
     body.setPosition(_x, _y);
     this->x = _x;
     this->y = _y;
 }

sf::Vector2f boing::getPosition() const
 {
     return body.getPosition();
 }

void boing::setVelocity(sf::Vector2f v)
 {
     speed = v;
 }

void boing::attach()
 {
     glue = true;
     speed = { 0.0f, 0.0f };
 }

void boing::deglue()
 {
     glue = false;
 }

const sf::RectangleShape& boing::getBody() const {
    return body;
}

sf::Vector2f boing::getSpeed() const {
    return speed;
}

void boing::setSpeed(const sf::Vector2f& newSpeed) {
    speed = newSpeed;
}

