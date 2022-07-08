#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Snake
{
public:
  Snake();

  int cols, lines, size, width, height, direction, num, points, healthPoints;
  float timer, delay;
  bool paused, gameover;

  sf::RenderWindow window;
  sf::Texture t1, t2, t3;
  sf::Sprite sp1, sp2, sp3;
  sf::Clock clock;
  sf::Font font;
  sf::Text text, pause, gameoverText, healthText;
  sf::FloatRect textBox;

  // Métodos
  void run_game();
  void collision();
  void pause_game();
  void game_over();
};
