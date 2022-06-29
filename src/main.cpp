#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecrap - 0.1");

  sf::RectangleShape object;
  object.setSize(sf::Vector2f(100.f, 100.f));
  object.setFillColor(sf::Color(0, 255, 0));
  object.setPosition(10.f, 10.f);

  // Dessa forma, usando a biblioteca <memory> podemos criar ponteiros na Heap
  // sem precisar rodar o delete e atribuir nulo ao ponteiro. Isso se chama
  // ponteiros inteligentes.
  // auto object = std::make_shared<sf::RectangleShape>();
  // object->setSize(sf::Vector2f(100.f, 100.f));
  // object->setFillColor(sf::Color(0, 255, 0));
  // object->setPosition(10.f, 10.f);

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

    window.clear();
    window.draw(object);
    window.display();
  }

  // Maneira correta de deletar um ponteiro na Heap
  // delete ponteiro;
  // ponteiro = nullptr;

  return EXIT_SUCCESS;
}
