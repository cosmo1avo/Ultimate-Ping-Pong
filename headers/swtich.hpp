#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ricochet.hpp"
#include "decel.hpp"
#include "hockey.hpp"
#include "basic.hpp"

class switcher {
public:
    static std::unique_ptr<boing> switchBall(int gamemode, const sf::Texture* ballTexture);
};

