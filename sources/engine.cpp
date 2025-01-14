#include "../headers/engine.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

engine::engine(sf::RenderWindow& _window, sf::View& _view)
    : _player1(&playertexture1, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(700.0f, 100.0f),1),
      _player2(&playertexture2, sf::Vector2u(2, 2), 0.5, 400.0f, sf::Vector2f(700.0f, 900.0f),2),
      wall1(&wallTexture, sf::Vector2f(15.0f, 1000.0f), sf::Vector2f(1150.0f, 500.0f)),
      wall2(&wallTexture, sf::Vector2f(15.0f, 1000.0f), sf::Vector2f(250.0f, 500.0f)),
      net(&wallTexture,sf::Vector2f(885,20),sf::Vector2f(700,500) ),
      score1(&score1texture, sf::Vector2f(100, 100), sf::Vector2f(1207.5f, 400)),
      score2(&score2texture, sf::Vector2f(100, 100), sf::Vector2f(1207.5f, 600)),
      gameselect(&gameselecttexture,sf::Vector2f(400,40),sf::Vector2f(700,500)),
      out1(&wallTexture, sf::Vector2f(242.5f, 1000.0f), sf::Vector2f(1278.75f, 500.0f)),
      out2(&wallTexture, sf::Vector2f(242.5f, 1000.0f), sf::Vector2f(121.25f, 500.0f)),
      boost(&gameselecttexture, sf::Vector2f(20, 20), sf::Vector2f(0,0)),
      window(_window),
      view(_view)
    {
        playertexture1.loadFromFile("./txt/paleta1.png");
        playertexture2.loadFromFile("./txt/paleta2.png");
        _player1 = player(&playertexture1, sf::Vector2u(2, 2), 0.5, 400.0f,sf::Vector2f(700.0f, 100.0f),1);
        _player2 = player(&playertexture2, sf::Vector2u(2, 2), 0.5, 400.0f,sf::Vector2f(700.0f, 900.0f),2);
        wallTexture.loadFromFile("./txt/green.png");
        balltexture.loadFromFile("./txt/ball.png");
        score1texture.loadFromFile("./txt/tabel.png");
        score2texture.loadFromFile("./txt/tabel.png");
        gameselecttexture.loadFromFile("./txt/gameselect.png");

        if (!playertexture1.loadFromFile("./txt/paleta1.png"))
            throw texture_load_exception("Failed to load texture for player 1.");
        if (!playertexture2.loadFromFile("./txt/paleta2.png"))
            throw texture_load_exception("Failed to load texture for player 2.");
        if (!wallTexture.loadFromFile("./txt/green.png"))
            throw texture_load_exception("Failed to load wall texture.");
        if (!balltexture.loadFromFile("./txt/ball.png"))
            throw texture_load_exception("Failed to load ball texture.");
        if (!score1texture.loadFromFile("./txt/tabel.png"))
            throw texture_load_exception("Failed to load score1 texture.");
        if (!score2texture.loadFromFile("./txt/tabel.png"))
            throw texture_load_exception("Failed to load score2 texture.");
        if (!gameselecttexture.loadFromFile("./txt/gameselect.png"))
            throw texture_load_exception("Failed to load game select texture.");

        score1.settextoffset(150, 0, 214, 214);
        score2.settextoffset(150, 0, 214, 214);
        ball = std::make_unique<basic>(&balltexture, sf::Vector2f(20, 20), sf::Vector2f(200, 200));

    }

    void engine::update(float deltatime)
    {
        deltatime = clock.restart().asSeconds();
        _player1.update(deltatime);
        _player2.update(deltatime);

        if(boost.getPosition() != sf::Vector2f(2000, 2000))
            boost.setPosition(ranposx, ranposy);

        static bool _glued = false;
        static arrow arrow;
        static speedmeter speedmeter;
        sf::Vector2f velocity(0.0f,0.0f);

        ball->update(deltatime);

        if (ball->getPosition().x < 200.0f || ball->getPosition().x > 1200.0f)
            throw out_of_bounds_exception("Ball is out of bounds.");

        float col1 = static_cast<float>(wall1.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col2 = static_cast<float>(wall2.getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col3 = static_cast<float>(wall1.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col4 = static_cast<float>(wall2.getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col5 = static_cast<float>(ball->getcollider().check_collision(_player1.getcollider(), 1.0f));
        float col6 = static_cast<float>(ball->getcollider().check_collision(_player2.getcollider(), 1.0f));
        float col7 = static_cast<float>(ball->getcollider().check_collision(wall1.getcollider(), 1.0f));
        float col8 = static_cast<float>(ball->getcollider().check_collision(wall2.getcollider(), 1.0f));
        float col9 = static_cast<float>(ball->getcollider().check_collision(boost.getcollider(), 0.0f));

        if(start)
        {
            gameselect.settextoffset(10, 0, 900, 200);
            gameselect.draw(window);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                gamemode = 1;
                ball = switcher::switchBall(gamemode, &balltexture);
                start = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                gamemode = 2;
                ball = switcher::switchBall(gamemode, &balltexture);
                start = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                gamemode = 3;
                ball = switcher::switchBall(gamemode, &balltexture);
                start = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                gamemode = 4;
                ball = switcher::switchBall(gamemode, &balltexture);
                start = false;
            }
        }
        if ((counter1 == 3450 || counter2 == 3450) || (counter1 == 1950 && counter2 == 150) || (counter1 == 150 && counter2 == 1950) || (counter1 == 2850 && counter2 == 450) || (counter1 == 450 && counter2 == 2850))
        {
            _glued = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !start) {
                serves = 0;
                ran = rand() % 2;
                startround = true;
                ball->deglue();
                score1.settextoffset(150, 0, 214, 214);
                score2.settextoffset(150, 0, 214, 214);
                std::cout << ran << std::endl;

                if (ran == 1)
                    ball->setVelocity(sf::Vector2f(0.0f, 200.0f));
                else
                    ball->setVelocity(sf::Vector2f(0.0f, -200.0f));

                counter1 = 150;
                counter2 = 150;
            } else {
                ball->setVelocity(sf::Vector2f(0.0f, 0.0f));
                ball->setPosition(700.0f, 500.0f);
            }
        }

        if((cur == 2 && (col7 != 0.0f || col8 != 0.0f) && gamemode != 2) || ball->getPosition().y > 1000.0f)
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

        if((cur == 1 && (col7 != 0.0f || col8 != 0.0f) && gamemode!=2) || ball->getPosition().y < 0.0f)
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

        if (serves != 0 && startround == true)
        {
            _player1.setPosition(700.0f);
            _player2.setPosition(700.0f);
            if(ran % 2 == 1)
                ball->setPosition(_player1.getPlayerPosition().x, _player1.getPlayerPosition().y);
            else
                ball->setPosition(_player2.getPlayerPosition().x, _player2.getPlayerPosition().y);
            ap = rand() %10;
            if(ap == 7)
                boost.setPosition(ranposx, ranposy);
        }

        if (serves % 5 == 0 && serves != 0 && startround == true)
        {
            ran ++;
            startround = false;
        }

        if (col1 != 0.0f)
            _player1.setPosition(1092.5f);

        if (col2 != 0.0f)
            _player1.setPosition(307.5f);

        if (col3 != 0.0f)
            _player2.setPosition(1092.5f);

        if (col4 != 0.0f)
            _player2.setPosition(307.5f);
        if(col9 != 0.0f)
        {
            velocity.x = ball->getSpeed().x * 3;
            velocity.y = ball->getSpeed().y * 3;
            ball->setVelocity(sf::Vector2f(velocity.x, velocity.y));
            boost.setPosition(2000.0f, 2000.0f);

        }

        if(!_glued && col5 != 0.0f)
        {
            startround = false;
            cur=1;
            _glued = true;
            ball->attach();
            ball->setPosition(_player1.getPlayerPosition().x, _player1.getPlayerPosition().y + 61);
            arrow.setPosition(ball->getPosition());
            _player1.blocaj(true);
        }

        if(!_glued && col6 != 0.0f)
        {
            startround = false;
            cur=2;
            _glued = true;
            ball->attach();
            ball->setPosition(_player2.getPlayerPosition().x, _player2.getPlayerPosition().y - 61);
            arrow.setPosition(ball->getPosition());
            _player2.blocaj(true);
        }

        if (_glued)
        {
            if(!speedselect)
            {
                static float speeddirection = 1;
                ballspeed += speeddirection * 200 * deltatime;
                if (ballspeed > 800.0f)
                {
                    ballspeed = 800.0f;
                    speeddirection = -1.0f;
                }
                else if (ballspeed < 400.0f)
                {
                    ballspeed = 400.0f;
                    speeddirection = 1.0f;
                }

                speedmeter.setX(ball->getPosition().x +50);
                speedmeter.setY(ball->getPosition().y + 200 - ballspeed/4);

                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && cur == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && cur == 2))
                {
                    if(!turn)
                    {
                        turn = true;
                        speedselect = 1;
                    }
                }
                else
                {
                    turn = false;
                }

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
                arrow.setPosition(ball->getPosition());
                arrow.setRotation(angle);
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && cur ==1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && cur ==2))
                {
                    if(!turn)
                    {
                        turn = true;
                        float radians = angle * 3.14159f / 180.0f;
                        velocity = sf::Vector2f(std::cos(radians) * ballspeed,std::sin(radians) * ballspeed );
                        ball->setVelocity(velocity);
                        ball->deglue();
                        _glued = false;

                        _player1.blocaj(false);
                        _player2.blocaj(false);
                        speedselect = 0;
                    }
                }
                else
                {
                    turn = false;
                }

            }

        }

        if(_glued)
        {
            if (speedselect == 0)
                speedmeter.draw(window);
            if (speedselect == 1)
                arrow.draw(window);
        }
        view.setCenter(700, 500);
        window.setView(view);

        if(!start)
        {
            _player1.draw(window);
            _player2.draw(window);
            wall1.draw(window);
            wall2.draw(window);
            out1.draw(window);
            out2.draw(window);
            net.draw(window);
            ball->draw(window);
            boost.draw(window);

            if (serves != 0)
            {
                score1.draw(window);
                score2.draw(window);
            }
        }

    }
    std::ostream& operator<<(std::ostream& stream, const engine& _engine)
    {
        stream << "Player 1: " << _engine._player1 << std::endl;
        stream << "Player 2: " << _engine._player2 << std::endl;
        stream << "Wall 1: " << _engine.wall1 << std::endl;
        stream << "Wall 2: " << _engine.wall2 << std::endl;
        stream << "Ball position " << _engine.ball->getPosition().y << std::endl;
        stream << "Ball speed" << _engine.ball->getSpeed().x << std::endl;
        return stream;
    }
