#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Helper.h>

int main() {
   sf::RenderWindow window(sf::VideoMode(800, 800), "Ultimate Ping-Pong");
   window.setFramerateLimit(60);
   while (window.isOpen())
   {
      sf::Event event{};
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }
      window.clear(sf::Color::Black);
      window.display();
   }
   return 0;
}
