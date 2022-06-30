#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Snake
{
public:
  Snake();

  int cols, lines, size, width, height, direction, num;

  sf::RenderWindow window;
  sf::Texture t1, t2, t3;
  sf::Sprite sp1, sp2, sp3;
  sf::Clock clock;

  float timer, delay;

  // Métodos
  void run_game();
  void collision();
};
