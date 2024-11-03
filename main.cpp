#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Helper.h>

class animation
{
public:
   animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime)
   {
      this->imagecount = imagecount;
      this->switchtime = switchtime;
      totaltime = 0.0f;
      currentimage.x=0;
      uvrect.width=texture->getSize().x / float(imagecount.x);
      uvrect.height=texture->getSize().y / float(imagecount.y);
   }
   void update(int row, float deltatime, bool faceright)
   {
      currentimage.y = row;
      totaltime += deltatime;
      if (totaltime >= switchtime)
      {
         totaltime -= switchtime;
         currentimage.x++;
         if (currentimage.x >= imagecount.x)
         {
            currentimage.x=0;
         }
      }
      uvrect.top=currentimage.y * uvrect.height;
      if(faceright)
      {
         uvrect.left=currentimage.x * uvrect.width;
         uvrect.width = abs(uvrect.width);
      }
      else
      {
         uvrect.left=(currentimage.x + 1) * abs(uvrect.width);
         uvrect.width = -abs(uvrect.width);
      }
   }

public:
   sf::IntRect uvrect;

private:
   sf::Vector2u imagecount;
   sf::Vector2u currentimage;

   float totaltime;
   float switchtime;
};


class player
{
public:
   player(sf::Texture* texture, sf::Vector2u imagecount, float switchtime,float speed):
      animation(texture, imagecount, switchtime)
   {
      this->speed = speed;
      row = 0;
      faceright = true;

      body.setSize(sf::Vector2f(100.0f, 100.0f));
      body.setPosition(400.0f, 400.0f);
      body.setTexture(texture);
   }
   void update(float deltatime)
   {
      sf::Vector2f movement(0.0f, 0.0f);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
         movement.x -= speed * deltatime;
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
         movement.x += speed * deltatime;
      if(movement.x == 0.0f)
         row = 0;
      else
      {
         row =1;
         if(movement.x>0.0f)
            faceright = true;
         else
            faceright = false;
      }
      animation.update(row,deltatime,faceright);
      body.setTextureRect(animation.uvrect);
      body.move(movement);
   }
      void draw(sf::RenderWindow& window)
   {
      window.draw(body);
   }

private:
   sf::RectangleShape body;
   animation animation;
   unsigned int row;
   float speed;
   bool faceright;

};

int main() {
   sf::RenderWindow window(sf::VideoMode(800, 800), "Ultimate Ping-Pong");
   sf::Texture playertexture;
   playertexture.loadFromFile("E:/fac/pooproject/UltimatePingPong/textures/test.png");

   player player(&playertexture, sf::Vector2u(2,2), 0.5, 100.0f);
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
         }
      }
      player.update(deltatime);
      window.clear(sf::Color::Black);
      player.draw(window);
      window.display();
   }

   return 0;
}
