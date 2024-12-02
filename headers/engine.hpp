#pragma once
#include "wall.hpp"
#include "player.hpp"
#include "boing.hpp"
#include "arrow.hpp"
#include "speedmeter.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class engine
{
public:
    engine(sf::RenderWindow& _window, sf::View& _view)
    : _player1(&playertexture1, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(400.0f, 75.0f),1),
      _player2(&playertexture2, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(400.0f, 725.0f),2),
      wall1(&wallTexture, sf::Vector2f(10.0f, 800.0f), sf::Vector2f(750.0f, 400.0f)),
      wall2(&wallTexture, sf::Vector2f(10.0f, 800.0f), sf::Vector2f(50.0f, 400.0f)),
      net(&nettexture,sf::Vector2f(690,20),sf::Vector2f(400,400) ),
      score1(&score1texture, sf::Vector2f(100, 100), sf::Vector2f(695, 300)),
      score2(&score2texture, sf::Vector2f(100, 100), sf::Vector2f(695, 500)),
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
        score1texture.loadFromFile("./txt/tabel.png");
        score2texture.loadFromFile("./txt/tabel.png");
        score1.settextoffset(150, 0, 214, 214);
        score2.settextoffset(150, 0, 214, 214);


    }

    void update(float deltatime = 0.0f)
    {
        deltatime = clock.restart().asSeconds();
        _player1.update(deltatime);
        _player2.update(deltatime);

        static bool _glued = false;
        static arrow arrow;
        static speedmeter speedmeter;
        sf::Vector2f velocity(0.0f,0.0f);

        ball.update(deltatime);

        float col1 = static_cast<float>(wall1.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col2 = static_cast<float>(wall2.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col3 = static_cast<float>(wall1.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col4 = static_cast<float>(wall2.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col5 = static_cast<float>(ball.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col6 = static_cast<float>(ball.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col7 = static_cast<float>(ball.getcollider().check_collision(wall1.getcollider(), 1.0f));
        float col8 = static_cast<float>(ball.getcollider().check_collision(wall2.getcollider(), 1.0f));

        if (counter1 == 3450 || counter2 == 3450)
        {
            _glued = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                serves = 0;
                ran = rand() % 2;
                startround = true;
                ball.deglue();
                score1.settextoffset(150, 0, 214, 214);
                score2.settextoffset(150, 0, 214, 214);
                std::cout << ran << std::endl;

                if (ran == 1)
                    ball.setVelocity(sf::Vector2f(0.0f, 200.0f));
                else
                    ball.setVelocity(sf::Vector2f(0.0f, -200.0f));

                counter1 = 150;
                counter2 = 150;
            } else {
                ball.setVelocity(sf::Vector2f(0.0f, 0.0f));
                ball.setPosition(400.0f, 400.0f);
            }
        }

        if((cur == 2 && (col7 != 0.0f || col8 != 0.0f)) || ball.getPosition().y > 800.0f)
        {
            startround = true;
            serves ++;
            if (serves > 1)
            {
                if (counter1 == 3150 && counter2 == 3150)
                {
                    counter1 += 600;
                    score1.settextoffset(counter1, 0, 214, 214);
                }
                else if (counter1 == 3750)
                {
                    counter1 -= 300;
                    score1.settextoffset(counter1, 0, 214, 214);
                }
                else if (counter2 == 3750)
                {
                    counter2 -= 600;
                    score2.settextoffset(counter2, 0, 214, 214);
                }
                else
                {
                    counter1 += 300;
                    score1.settextoffset(counter1, 0, 214, 214);
                }
            }
            if (serves == 1)
            {
                ran = 1;
            }
        }

        if((cur == 1 && (col7 != 0.0f || col8 != 0.0f)) || ball.getPosition().y < 0.0f)
        {
            startround = true;
            serves++;
            if (serves > 1)
            {
                if (counter1 == 3150 && counter2 == 3150)
                {
                    counter2 += 600;
                    score2.settextoffset(counter2, 0, 214, 214);
                }
                else if (counter2 == 3750)
                {
                    counter2 -= 300;
                    score2.settextoffset(counter2, 0, 214, 214);
                }
                else if (counter1 == 3750)
                {
                    counter1 -= 600;
                    score1.settextoffset(counter1, 0, 214, 214);
                }
                else
                {
                    counter2 += 300;
                    score2.settextoffset(counter2, 0, 214, 214);
                }
            }
            if (serves == 1)
            {
                ran = 2;
            }
        }

        if (serves != 0  && ran % 2 == 1 && startround == true)
        {
            ball.setPosition(_player1.getPosition().x, _player1.getPosition().y);
        }
        if (serves != 0 && ran % 2 == 0 && startround == true)
        {
            ball.setPosition(_player2.getPosition().x, _player2.getPosition().y);
        }

        if (serves % 5 == 0 && serves != 0 && startround == true)
        {
            ran ++;
            startround = false;
        }

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
            startround = false;
            cur=1;
            _glued = true;
            ball.attach();
            ball.setPosition(_player1.getPosition().x, _player1.getPosition().y + 61);
            arrow.setPosition(ball.getPosition());
            _player1.blocaj(true);
        }

        if(!_glued && col6 != 0.0f)
        {
            startround = false;
            cur=2;
            _glued = true;
            ball.attach();
            ball.setPosition(_player2.getPosition().x, _player2.getPosition().y - 61);
            arrow.setPosition(ball.getPosition());
            _player2.blocaj(true);
        }

        if (_glued)
        {
            if(!speedselect)
            {
                static float speeddirection = 1;
                ballspeed += speeddirection * 100 * deltatime;
                if (ballspeed > 500.0f)
                {
                    ballspeed = 500.0f;
                    speeddirection = -1.0f;
                }
                else if (ballspeed < 250.0f)
                {
                    ballspeed = 250.0f;
                    speeddirection = 1.0f;
                }

                speedmeter.setX(ball.getPosition().x +50);
                speedmeter.setY(ball.getPosition().y + 200 - ballspeed/2);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    speedselect = 1;
            }
            else if(speedselect == 1)
            {
                static float angle = 0.0f;
                static float direction = 1;
                angle += direction * 100 * deltatime;
                if (cur == 1)
                {
                    if (angle > 150.0f)
                    {
                        angle = 150.0f;
                        direction = -1;
                    }
                    else if (angle < 30.0f)
                    {
                        angle = 30.0f;
                        direction = 1;
                    }
                }
                else if (cur == 2)
                {
                    if (angle > 330.0f)
                    {
                        angle = 330.0f;
                        direction = -1;
                    }
                    else if (angle < 210.0f)
                    {
                        angle = 210.0f;
                        direction = 1;
                    }
                }
                arrow.setPosition(ball.getPosition());
                arrow.setRotation(angle);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    float radians = angle * 3.14159f / 180.0f;
                    velocity = sf::Vector2f(std::cos(radians) * ballspeed,std::sin(radians) * ballspeed );
                    ball.setVelocity(velocity);
                    ball.deglue();
                    _glued = false;

                    _player1.blocaj(false);
                    _player2.blocaj(false);
                    speedselect = 0;
                }

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

        if (serves != 0)
        {
            score1.draw(window);
            score2.draw(window);
        }

        if(_glued)
        {
            if (speedselect == 0)
                speedmeter.draw(window);
            if (speedselect == 1)
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
    sf::Texture score1texture;
    sf::Texture score2texture;
    player _player1;
    player _player2;
    wall wall1;
    wall wall2;
    wall net;
    wall score1;
    wall score2;
    boing ball;
    bool startround = true;
    int ran = rand() %2;
    int cur = 0;
    float ballspeed = 75.0f;
    int speedselect = 0;
    int counter1 = 3450;
    int counter2 = 3450;
    int serves = 0;
    sf::RenderWindow& window;
    sf::View& view;
    sf::Clock clock;
};