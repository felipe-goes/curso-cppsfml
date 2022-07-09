#include "SFML/Graphics/Rect.hpp"
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Plataforma 2D",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(60);

  const float height_floor = 100.f;
  float frame = 0.f;

  sf::Texture texture, floor_texture, bg_texture;
  texture.loadFromFile("./resources/imgs/afro.png");
  floor_texture.loadFromFile("./resources/imgs/floormax.jpg");
  bg_texture.loadFromFile("./resources/imgs/bg.jpg");
  sf::Sprite sprite(texture, sf::IntRect(0, 0, 43, 82)), floor(floor_texture),
    bg(bg_texture);
  sprite.setPosition(0, window.getSize().y - sprite.getGlobalBounds().height -
                          height_floor);

  // floor
  floor.setPosition(0.f, window.getSize().y - height_floor);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      sprite.move(8.f, 0);
      frame += 0.5f;
      if (frame > 6.f)
      {
        frame -= 6.f;
      }
      sprite.setTextureRect(sf::IntRect(43 * (int)frame, 0, 43, 82));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      sprite.move(-8.f, 0);
      frame += 0.5f;
      if (frame > 6.f)
      {
        frame -= 6.f;
      }
      sprite.setTextureRect(sf::IntRect(43 * (int)frame + 43, 0, -43, 82));
    }

    window.clear(sf::Color::Yellow);
    window.draw(bg);
    window.draw(floor);
    window.draw(sprite);
    window.display();
  }

  return EXIT_SUCCESS;
}
