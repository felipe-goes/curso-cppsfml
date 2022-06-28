#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Fundamentos Iniciais");
  sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
  rectangle.setFillColor(sf::Color::Green);
  rectangle.setPosition(
    (window.getSize().x / 2.f) - (rectangle.getSize().x / 2.f),
    (window.getSize().y / 2.f) - (rectangle.getSize().y / 2.f));

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      auto position = sf::Mouse::getPosition(window);

      if (position.x < window.getSize().x - rectangle.getSize().x &&
          position.y < window.getSize().y - rectangle.getSize().y)
      {
        rectangle.setPosition(position.x, position.y);
      }

      if (position.x > 600)
      {
        rectangle.setFillColor(sf::Color::Red);
      }
      else
      {
        rectangle.setFillColor(sf::Color::Green);
      }

      window.clear();
      window.draw(rectangle);
      window.display();
    }
  }

  return EXIT_SUCCESS;
}
