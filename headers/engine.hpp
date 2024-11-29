#pragma once
#include "wall.hpp"
#include "player.hpp"
#include "boing.hpp"
#include "arrow.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class engine
{
public:
    engine(sf::RenderWindow& _window, sf::View& _view)
    : _player1(&playertexture1, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(400.0f, 200.0f),1),
      _player2(&playertexture2, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(400.0f, 400.0f),2),
      wall1(&wallTexture, sf::Vector2f(10.0f, 800.0f), sf::Vector2f(750.0f, 400.0f)),
      wall2(&wallTexture, sf::Vector2f(10.0f, 800.0f), sf::Vector2f(50.0f, 400.0f)),
      net(&nettexture,sf::Vector2f(690,20),sf::Vector2f(400,400) ),
      ball(&balltexture, sf::Vector2f(20,20),sf::Vector2f(200,200)),
      window(_window),
      view(_view)
    {
        playertexture1.loadFromFile("./txt/test1.png");
        playertexture2.loadFromFile("./txt/test2.png");
        _player1 = player(&playertexture1, sf::Vector2u(2, 2), 0.5, 400.0f,sf::Vector2f(400.0f, 75.0f),1);
        _player2 = player(&playertexture2, sf::Vector2u(2, 2), 0.5, 400.0f,sf::Vector2f(400.0f, 725.0f),2);
        wallTexture.loadFromFile("./txt/green.png");
        nettexture.loadFromFile("./txt/red.jpg");
        balltexture.loadFromFile("./txt/blue.png");

    }

    void update(float deltatime = 0.0f)
    {
        deltatime = clock.restart().asSeconds();
        _player1.update(deltatime);
        _player2.update(deltatime);

        static bool _glued = false;
        static arrow arrow;
        static const player* cur=nullptr;
        sf::Vector2f velocity(0.0f,0.0f);
        if(start)
        {
            if(ran == 1)
                velocity = sf::Vector2f(0.0f, 200.0f);

            else
                velocity = sf::Vector2f(0.0f, -200.0f);
            ball.setVelocity(velocity);
        }
        ball.update(deltatime);

        float col1 = static_cast<float>(wall1.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col2 = static_cast<float>(wall2.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col3 = static_cast<float>(wall1.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col4 = static_cast<float>(wall2.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col5 = static_cast<float>(ball.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col6 = static_cast<float>(ball.getcollider().check_collision(_player2.getcollider(), 1.0f));

        if (col1 != 0.0f)
            _player1.setPosition(695.0f);

        if (col2 != 0.0f)
            _player1.setPosition(105.0f);

        if (col3 != 0.0f)
            _player2.setPosition(695.0f);

        if (col4 != 0.0f)
            _player2.setPosition(105.0f);

        if(!_glued && col5 != 0.0f)
        {
            start=false;
            _glued = true;
            ball.attach();
            cur=&_player1;
            ball.setPosition(_player1.getPosition().x, _player1.getPosition().y + 61);
            arrow.setPosition(ball.getPosition());
            _player1.blocaj(true);
        }

        if(!_glued && col6 != 0.0f)
        {
            start=false;
            _glued = true;
            ball.attach();
            cur=&_player2;
            ball.setPosition(_player2.getPosition().x, _player2.getPosition().y - 61);
            arrow.setPosition(ball.getPosition());
            _player2.blocaj(true);
        }

        if (_glued) {
            static float angle = 0.0f;
            arrow.setPosition(ball.getPosition());
            arrow.setRotation(angle);

            angle += 100 * deltatime;
            if (angle > 360.0f) angle -= 360.0f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                float radians = angle * 3.14159f / 180.0f;
                float maxspeed = 300.0f;
                velocity = sf::Vector2f(std::cos(radians) * maxspeed,std::sin(radians) * maxspeed );
                ball.setVelocity(velocity);
                ball.deglue();
                _glued = false;

                _player1.blocaj(false);
                _player2.blocaj(false);
            }
        }

        view.setCenter(400, 400);
        window.setView(view);

        _player1.draw(window);
        _player2.draw(window);
        wall1.draw(window);
        wall2.draw(window);
        net.draw(window);
        ball.draw(window);

        if(_glued)
        {
            arrow.draw(window);
        }

    }
    friend std::ostream& operator<<(std::ostream& stream, const engine& _engine)
    {
        stream << "Player 1: " << _engine._player1 << std::endl;
        stream << "Player 2: " << _engine._player2 << std::endl;
        stream << "Wall 1: " << _engine.wall1 << std::endl;
        stream << "Wall 2: " << _engine.wall2 << std::endl;
        return stream;
    }
private:
    sf::Texture playertexture1;
    sf::Texture playertexture2;
    sf::Texture wallTexture;
    sf::Texture nettexture;
    sf::Texture balltexture;
    player _player1;
    player _player2;
    wall wall1;
    wall wall2;
    wall net;
    boing ball;
    bool start = true;
    int ran = rand() %2;
    sf::RenderWindow& window;
    sf::View& view;
    sf::Clock clock;
};