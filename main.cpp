#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Helper.h>
#include "headers/player.hpp"
#include "headers/global.hpp"
#include "headers/resizeview.hpp"
#include "headers/collider.hpp"
#include "headers/wall.hpp"
#include "headers/engine.hpp"
#include "headers/switch_exception.hpp"

int main()
{
   try
   {
      sf::RenderWindow window(sf::VideoMode(1400, 1000), "Ultimate Ping-Pong");
      sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));
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
                  resizeview(window,view);
               break;
               default:
                  break;
            }
            //std::cout << _engine << std::endl;
         }

         window.clear(sf::Color(140, 165, 174, 255));
         _engine.update(deltatime);
         window.setView(view);
         window.display();
      }
   }
   catch (const texture_load_exception& e) {
      std::cerr << "Eroare la incarcarea texturii: " << e.what() << std::endl;
   }
   catch (const out_of_bounds_exception& e) {
      std::cerr << "Eroare: " << e.what() << std::endl;
   }
   catch (const switch_exception& e) {
      std::cerr << "Eroare: " << e.what() << std::endl;
   }

   return 0;
}
