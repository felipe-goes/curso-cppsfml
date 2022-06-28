#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Textos e Fontes");
  sf::Font arial, pixel;
  if (!arial.loadFromFile("../resources/fonts/arial.ttf") ||
      !pixel.loadFromFile("../resources/fonts/PixelBloated.ttf"))
  {
    std::cerr << "Falha ao ler a fonte\n";
    return EXIT_FAILURE;
  }

  sf::Text score("Score: 0", arial, 32), life("Life: 3", pixel, 32);
  score.setPosition(sf::Vector2f(1110.f, 0.f));

  sf::Color rgb(55, 44, 77);
  score.setFillColor(rgb);

  life.setPosition(sf::Vector2f(10.f, 0.f));
  life.setFillColor(sf::Color::Red);

  int num{}, num2 = 3;
  bool pressed = false;

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

    if (event.type == event.MouseButtonReleased &&
        event.type == event.MouseButtonPressed)
    {
      pressed = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && pressed)
    {
      --num2;
      pressed = !pressed;
      life.setString("Life: " + std::to_string(num2));
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
    {
      ++num;
      // std::cout << "Você clicou com o botão esquerdo! " << num << "
      // vezes.\n";
      score.setString("Score: " + std::to_string(num));
      pressed = true;
    }

    if (num2 < 0)
    {
      std::cout << "Game Over\n";
      break;
    }

    window.clear(sf::Color::White);
    window.draw(score);
    window.draw(life);
    window.display();
  }

  return EXIT_SUCCESS;
}
