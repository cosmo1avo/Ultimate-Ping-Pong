#pragma once
#include "wall.hpp"
#include "player.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class engine
{
public:
    engine(sf::RenderWindow& _window, sf::View& _view)
    : _player1(&playertexture1, sf::Vector2u(2, 2), 0.5, 100.0f, sf::Vector2f(400.0f, 200.0f),1),
      _player2(&playertexture2, sf::Vector2u(2, 2), 0.5, 100.0f, sf::Vector2f(400.0f, 400.0f),2),
      wall1(&wallTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(800.0f, 300.0f)),
      wall2(&wallTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(50.0f, 300.0f)),
      window(_window),
      view(_view)
    {
        playertexture1.loadFromFile("./txt/test1.png");
        playertexture2.loadFromFile("./txt/test2.png");
        _player1 = player(&playertexture1, sf::Vector2u(2, 2), 0.5, 100.0f,sf::Vector2f(400.0f, 200.0f),1);
        _player2 = player(&playertexture2, sf::Vector2u(2, 2), 0.5, 100.0f,sf::Vector2f(400.0f, 400.0f),2);
        wallTexture.loadFromFile("./txt/green.png");

    }

    void update(float deltatime = 0.0f)
    {
        deltatime = clock.restart().asSeconds();
        _player1.update(deltatime);
        _player2.update(deltatime);

        float col1 = static_cast<float>(wall1.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col2 = static_cast<float>(wall2.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col3 = static_cast<float>(wall1.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col4 = static_cast<float>(wall2.getcollider().check_collision(_player2.getcollider(), 1.0f));

        if (col1 != 0.0f) {
            _player1.move(-col1 * 2.0f, 0.0f);
        }
        if (col2 != 0.0f) {
            _player1.move(col2 * 2.0f, 0.0f);
        }
        if (col3 != 0.0f)
            _player2.move(-col3 * 2.0f, 0.0f);

       if (col4 != 0.0f)
           _player2.move(col4 * 2.0f, 0.0f);
        view.setCenter(400, 400);
        window.setView(view);

        _player1.draw(window);
        _player2.draw(window);
        wall1.draw(window);
        wall2.draw(window);
    }

private:
    sf::Texture playertexture1;
    sf::Texture playertexture2;
    sf::Texture wallTexture;
    player _player1;
    player _player2;
    wall wall1;
    wall wall2;
    sf::RenderWindow& window;
    sf::View& view;
    sf::Clock clock;
};