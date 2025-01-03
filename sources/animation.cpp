#include "../headers/animation.hpp"

animation::animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime)
{
    this->imagecount = imagecount;
    this->switchtime = switchtime;
    totaltime = 0.0f;
    currentimage.x = 0;

    uvrect.width = texture->getSize().x / static_cast<int>(imagecount.x);
    uvrect.height = texture->getSize().y / static_cast<int>(imagecount.y);
}



void animation::update(int row, float deltatime, bool faceright) {
    currentimage.y = row;
    totaltime += deltatime;

    if (totaltime >= switchtime) {
        totaltime -= switchtime;
        currentimage.x++;
        if (currentimage.x >=imagecount.x) {
            currentimage.x = 0;
        }
    }

    uvrect.top = static_cast<int>(currentimage.y * uvrect.height);
    if (faceright) {
        uvrect.left = static_cast<int>(currentimage.x * uvrect.width);
        uvrect.width = std::abs(uvrect.width);
    } else {
        uvrect.left = static_cast<int>((currentimage.x + 1) * std::abs(uvrect.width));
        uvrect.width = -std::abs(uvrect.width);
    }
}


sf::IntRect animation::getuvrect()
{
    return this->uvrect;
}