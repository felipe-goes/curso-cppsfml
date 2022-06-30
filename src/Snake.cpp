#include "Snake.hpp"
#include "Game.hpp"

// TODO perder ponto ou o game se bater na própria cauda
// TODO verificar se a nova posição da fruta está dentro da cauda
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
  points = 0;
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

  font.loadFromFile("./resources/fonts/arial.ttf");
  text.setFont(font);
  text.setString("Pontos: " + std::to_string(points));
  text.setFillColor(sf::Color::White);
  text.setPosition(10, 10);
}

void Snake::run_game()
{
  while (window.isOpen())
  {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if (timer > delay)
    {
      timer = 0;
      collision();
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

    for (int i{}; i < num; ++i)
    {
      sp2.setPosition(s[i].x * size, s[i].y * size);
      window.draw(sp2);
    }

    sp3.setPosition(fruit.x * size, fruit.y * size);
    window.draw(sp3);

    window.draw(text);

    window.display();
  }
}

void Snake::collision()
{
  for (int i = num; i > 0; --i)
  {
    s[i].x = s[i - 1].x;
    s[i].y = s[i - 1].y;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    direction = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    direction = 1;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    direction = 2;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    direction = 3;
  }

  switch (direction)
  {
  case 0:
    s[0].x += 1;
    break;
  case 1:
    s[0].x -= 1;
    break;
  case 2:
    s[0].y -= 1;
    break;
  case 3:
    s[0].y += 1;
    break;
  }

  if (s[0].x == fruit.x && s[0].y == fruit.y)
  {
    points += 10;
    text.setString("Pontos: " + std::to_string(points));
    ++num;
    fruit.x = std::rand() % cols;
    fruit.y = std::rand() % lines;
  }

  if (s[0].x > cols)
  {
    s[0].x = 0;
  }
  if (s[0].x < 0)
  {
    s[0].x = cols;
  }

  if (s[0].y > lines)
  {
    s[0].y = 0;
  }
  if (s[0].y < 0)
  {
    s[0].y = lines;
  }

}
