#include "../headers/collider.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

collider::collider(sf::RectangleShape& body):
body(body)
{

}

bool collider::check_collision(collider other,float push)
{
    sf::Vector2f otherposition=other.getposition();
    sf::Vector2f otherhalfsize=other.gethalfsize();
    sf::Vector2f thisposition=getposition();
    sf::Vector2f thishalfsize=gethalfsize();

    float deltax=otherposition.x - thisposition.x;
    float deltay=otherposition.y - thisposition.y;
    float intersectx=fabs(deltax) - (otherhalfsize.x + thishalfsize.x);
    float intersecty=fabs(deltay) - (otherhalfsize.y + thishalfsize.y);

    if(intersectx < 0.0f && intersecty < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if(intersectx > intersecty)
        {
            if(deltax > 0.0f)
            {
                movef(intersectx * (1.0f - push), 0.0f);
                other.movef(-intersectx * push, 0.0f);
            }
            else
            {
                movef(-intersectx * (1.0f - push), 0.0f);
                other.movef(intersectx * push, 0.0f);
            }
        }
        else
        {
            if(deltay > 0.0f)
            {
                movef(0.0f,intersecty * (1.0f - push));
                other.movef(0.0f,-intersecty * push);
            }
            else
            {
                movef(0.0f,-intersecty * (1.0f - push));
                other.movef(0.0f, intersecty * push);
            }
        }

        return 1.0f;
    }
    return 0.0f;
}
void collider::movef(float dx, float dy)
{
    body.move(dx,dy);
}
sf::Vector2f collider::getposition()
{
    return body.getPosition();
}
sf::Vector2f collider::gethalfsize()
{
    return body.getSize() / 2.0f;
}

