#include "../headers/swtich.hpp"

std::unique_ptr<boing> switcher::switchBall(int gamemode, const sf::Texture* ballTexture) {
    switch (gamemode) {
        case 1:
            return std::make_unique<basic>(ballTexture, sf::Vector2f(20, 20), sf::Vector2f(200, 200));
        case 2: {
            auto ricochetBall = std::make_unique<ricochet>(ballTexture, sf::Vector2f(20, 20), sf::Vector2f(200, 200));
            return std::unique_ptr<boing>(ricochetBall->clone());
        }
        case 3: {
            auto decelBall = std::make_unique<decel>(ballTexture, sf::Vector2f(20, 20), sf::Vector2f(200, 200));
            return std::unique_ptr<boing>(decelBall->clone());
        }
        case 4: {
            auto hockeyBall = std::make_unique<hockey>(ballTexture, sf::Vector2f(20, 20), sf::Vector2f(200, 200));
            return std::unique_ptr<boing>(hockeyBall->clone());
        }
        default:
            throw std::invalid_argument("Invalid game mode.");
    }
}
