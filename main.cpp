#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "headers/animation.hpp"
#include "headers/player.hpp"
#include "headers/global.hpp"
#include "headers/resizeview.hpp"
#include "headers/collider.hpp"
#include "headers/wall.hpp"
#include "headers/engine.hpp"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 800), "Ultimate Ping-Pong");
   sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
   engine _engine(window, view);
   sf::Clock clock;

   window.setFramerateLimit(60);

   while (window.isOpen())
   {
      float deltatime = clock.restart().asSeconds();
      sf::Event evnt{};

      while (window.pollEvent(evnt))
      {
         switch (evnt.type)
         {
            case sf::Event::Closed:
               window.close();
            break;

            case sf::Event::Resized:
               resizeview(window, view);
            break;

            case sf::Event::KeyPressed:
               if (evnt.key.code == sf::Keyboard::Escape)
               {
                  window.close();
               }
            break;

            default:
               break;
         }
      }

      _engine.update(deltatime);

      window.clear(sf::Color::Black);

      window.setView(view);
      _engine.update(deltatime);

      window.display();
   }

   return 0;
}
