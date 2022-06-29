#include <SFML/Graphics.hpp>
#include <ctime>
#include <experimental/random> // se tiver no windows use o <ctime> std::rand()
#include <iostream>

int main()
{
  std::srand(std::time(nullptr));

  sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecrap - 0.1");
  window.setFramerateLimit(60);

  sf::RectangleShape object;
  object.setSize(sf::Vector2f(100.f, 100.f));
  object.setFillColor(sf::Color(0, 255, 0));

  float x = static_cast<float>(std::experimental::randint(
    10, static_cast<int>(window.getSize().x - object.getSize().x)));
  object.setPosition(x, 10.f);

  sf::Vector2i pos_mouse_win; // Posição do mouse em relação a janela(window)
  sf::Vector2f pos_mouse_coord; // Armazenará as coordenadas mapeadas

  int points{}; // maneira moderna de inicializar com 0

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

      pos_mouse_win = sf::Mouse::getPosition(window);
      pos_mouse_coord = window.mapPixelToCoords(pos_mouse_win);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if (object.getGlobalBounds().contains(pos_mouse_coord))
      {
        x = static_cast<float>(std::experimental::randint(
          10, static_cast<int>(window.getSize().x - object.getSize().x)));
        object.setPosition(x, 10.f);
        std::cout << "Sua pontuação agore é: " << ++points << '\n';
      }
    }

    if (object.getPosition().y > window.getSize().y)
    {
      x = static_cast<float>(std::experimental::randint(
        10, static_cast<int>(window.getSize().x - object.getSize().x)));
      object.setPosition(x, 10.f);
    }
    object.move(0.f, 5.f);

    window.clear();
    window.draw(object);
    window.display();
  }

  // Maneira correta de deletar um ponteiro na Heap
  // delete ponteiro;
  // ponteiro = nullptr;

  return EXIT_SUCCESS;
}
