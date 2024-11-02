#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Helper.h>

class animation
{
public:
   animation(sf::Texture* texture, sf::Vector2u imageCount, float switchtime);
   ~animation();

public:
   sf::IntRect uvrect;

private:
   sf::Vector2u imagecount;
   sf::Vector2u currentimage;

   float totaltime;
   float switchtime;
};


class racket
{
public:
   std::string name;

   std::string returnname()
   {
      return name;
   }

};

int main() {
   sf::RenderWindow window(sf::VideoMode(800, 800), "Ultimate Ping-Pong");
   sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
   player.setPosition(400.0f, 400.0f);
   sf::Texture playertexture;
   playertexture.loadFromFile("E:/fac/pooproject/UltimatePingPong/textures/test.png");
   player.setTexture(&playertexture);
   sf::Vector2u texturesize = playertexture.getSize();
   texturesize.x /= 2;
   player.setTextureRect(sf::IntRect(texturesize.x , 0, texturesize.x, texturesize.y));
   window.setFramerateLimit(60);
   while (window.isOpen())
   {
      sf::Event evnt{};
      while (window.pollEvent(evnt))
      {
         switch (evnt.type)
         {
            case sf::Event::Closed:
               window.close();
               break;
         }
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
         player.move(-0.5f, 0.0f);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
         player.move(0.5f, 0.0f);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
         player.move(0.0f, -0.5f);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
         player.move(0.0f, 0.5f);
      window.clear(sf::Color::Black);
      window.draw(player);
      window.display();
   }

   return 0;
}
