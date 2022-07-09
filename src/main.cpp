#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Plataforma 2D",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(60);

  sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 60.f));
  floor.setPosition(0.f, window.getSize().y - 60.f);
  floor.setFillColor(sf::Color::Black);

  sf::Texture texture;
  texture.loadFromFile("./resources/imgs/afro.png");
  sf::Sprite sprite(texture, sf::IntRect(0, 0, 43, 82));
  sprite.setPosition(0, window.getSize().y - sprite.getGlobalBounds().height -
                          60.f);

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
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      sprite.move(-8.f, 0);
    }

    window.clear(sf::Color::Yellow);
    window.draw(floor);
    window.draw(sprite);
    window.display();
  }

  return EXIT_SUCCESS;
}
