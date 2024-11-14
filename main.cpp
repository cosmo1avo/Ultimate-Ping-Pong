#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Helper.h>
#include "headers/animation.hpp"
#include "headers/player.hpp"
#include "headers/global.hpp"
#include "headers/resizeview.hpp"
#include "headers/collider.hpp"
#include "headers/wall.hpp"

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 800), "Ultimate Ping-Pong");
   sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_HEIGHT,VIEW_HEIGHT));
   sf::Texture playertexture;
   playertexture.loadFromFile("./textures/test.png");

   player player(&playertexture, sf::Vector2u(2,2), 0.5, 100.0f);

   wall wall1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(800.0f,300.0f));
   wall wall2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(50.0f,300.0f));
   float deltatime=0.0f;
   sf::Clock clock;

   window.setFramerateLimit(60);
   while (window.isOpen())
   {
      deltatime = clock.restart().asSeconds();
      sf::Event evnt{};
      while (window.pollEvent(evnt))
      {
         switch (evnt.type)
         {
            case sf::Event::Closed:
               window.close();
               break;
            case sf::Event::Resized:
               resizeview(window,view);
               break;
            default:
               break;
         }
      }
      player.update(deltatime);
      bool col1=wall1.getcollider().check_collision(player.getcollider(),1.0f);
      //wall1.getcollider().check_collision(player.getcollider(),1.0f);
      player.move(-col1 * 2.0f, 0.0f);

      bool col2=wall2.getcollider().check_collision(player.getcollider(),1.0f);
      player.move(col2 * 2.0f, 0.0f);
      view.setCenter(400,400);
      window.clear(sf::Color::Black);
      window.setView(view);
      player.draw(window);
      wall1.draw(window);
      wall2.draw(window);
      window.display();
   }

   return 0;
}
