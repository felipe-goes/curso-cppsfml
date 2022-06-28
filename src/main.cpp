#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Fundamentos Iniciais");

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      window.clear();
      // window.draw();
      window.display();
    }
  }

  return EXIT_SUCCESS;
}
