#ifndef MINECRAP_H
#define MINECRAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <experimental/random> // se tiver no windows use o <ctime> std::rand()
#include <iostream>

class Minecrap
{
public:
  Minecrap();
  sf::RenderWindow window;

  // MUSICA E SONOPLASTIA(EFEITOS DE SOM OU FX)
  sf::SoundBuffer pop, gameover_buffer;
  sf::Sound pop_sound, gameover_sound;
  sf::Music music;

  bool pressed, gameover, paused;
  int points, health; // maneira moderna de inicializar com 0
  float velocity, x, obj_vel_max, obj_vel;

  sf::Font font, jet;
  sf::Text score, life, gameover_text, f1, paused_text;

  sf::Texture texture, bg, hammer, stop;

  sf::Sprite object, fundo, ham, stop_sprite;

  sf::Vector2i pos_mouse_win; // Posição do mouse em relação a janela(window)
  sf::Vector2f pos_mouse_coord; // Armazenará as coordenadas mapeadas

  // OBJETOS
  std::vector<sf::Sprite> objs;
  size_t max_objs;

  sf::Vector2i current_position;

  // Funções
  void code_game();
  void game_over();
  void pause_game();
  void loop_events();
  void run_game();
};

#endif
