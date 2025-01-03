#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class animation
{
public:
    animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime);

    void update(int row, float deltatime, bool faceright);

    sf::IntRect getuvrect();

private:
    sf::IntRect uvrect;
    sf::Vector2u imagecount;
    sf::Vector2u currentimage;

    float totaltime;
    float switchtime;
};
