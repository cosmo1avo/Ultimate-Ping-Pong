#pragma once
#include "wall.hpp"
#include "player.hpp"
#include "boing.hpp"
#include "arrow.hpp"
#include "speedmeter.hpp"
#include "ricochet.hpp"
#include "decel.hpp"
#include "hockey.hpp"
#include "basic.hpp"
#include "engine_exceptions.hpp"
#include "texture_load_exception.hpp"
#include "out_of_bounds_exception.hpp"
#include "swtich.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class engine
{
public:
    engine(sf::RenderWindow& _window, sf::View& _view);

    void update(float deltatime = 0.0f);

    friend std::ostream& operator<<(std::ostream& stream, const engine& _engine);
private:
    sf::Texture playertexture1;
    sf::Texture playertexture2;
    sf::Texture wallTexture;
    sf::Texture balltexture;
    sf::Texture score1texture;
    sf::Texture score2texture;
    sf::Texture gameselecttexture;
    player _player1;
    player _player2;
    wall wall1;
    wall wall2;
    wall net;
    wall score1;
    wall score2;
    wall gameselect;
    wall out1;
    wall out2;
    std::unique_ptr<boing> ball;
    bool startround = true;
    bool start = true;
    bool turn = false;
    int ran = rand() %2;
    int cur = 0;
    float ballspeed = 75.0f;
    int speedselect = 0;
    int counter1 = 3450;
    int counter2 = 3450;
    int serves = 0;
    int gamemode = 0;
    sf::RenderWindow& window;
    sf::View& view;
    sf::Clock clock;
};