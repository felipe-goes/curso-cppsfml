#include "Snake.hpp"
#include "Game.hpp"

SnakeGame s[100];
Fruit fruit;

Snake::Snake()
{
  cols = 20;
  lines = 13;
  size = 64;
  width = size * cols;
  height = size * lines;
  direction = 0;
  num = 4;
  timer = 0.f;
  delay = 0.1f;
  fruit.x = fruit.y = 10;

  window.create(sf::VideoMode(width, height), "Snake Game 1.0",
                sf::Style::Titlebar | sf::Style::Close);
  window.setPosition(sf::Vector2i(0, 0));

  t1.loadFromFile("./resources/imgs/bg.png");
  t2.loadFromFile("./resources/imgs/snake.png");
  t3.loadFromFile("./resources/imgs/fruta.png");

  sp1.setTexture(t1);
  sp2.setTexture(t2);
  sp3.setTexture(t3);
}

void Snake::run_game()
{
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

    window.clear(sf::Color::White);

    for (int i{}; i < cols; ++i)
    {
      for (int j{}; j < lines; ++j)
      {
        sp1.setPosition(i * size, j * size);
        window.draw(sp1);
      }
    }

    window.display();
  }
}
