#pragma once
#include "wall.hpp"
#include "player.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class engine
{
public:
    engine(sf::RenderWindow& _window, sf::View& _view)
        : window(_window), view(_view),
          _player(&playertexture, sf::Vector2u(2, 2), 0.5, 100.0f),
          wall1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(800.0f, 300.0f)),
          wall2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(50.0f, 300.0f))
    {

        playertexture.loadFromFile("./txt/test.png");
        _player = player(&playertexture, sf::Vector2u(2, 2), 0.5, 100.0f);

    }

    void update(float deltatime = 0.0f)
    {
        deltatime = clock.restart().asSeconds();
        _player.update(deltatime);

        float col1 = static_cast<float>(wall1.getcollider().check_collision(_player.getcollider(), 1.0f));
        float col2 = static_cast<float>(wall2.getcollider().check_collision(_player.getcollider(), 1.0f));

        _player.move(-col1 * 2.0f, 0.0f);
        _player.move(col2 * 2.0f, 0.0f);

        view.setCenter(400, 400);
        window.setView(view);

        _player.draw(window);
        wall1.draw(window);
        wall2.draw(window);
    }

private:
    sf::Texture playertexture;
    player _player;
    wall wall1;
    wall wall2;
    sf::RenderWindow& window;
    sf::View& view;
    sf::Clock clock;
};
