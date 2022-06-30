#include "SFML/Graphics/Color.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <experimental/random> // se tiver no windows use o <ctime> std::rand()
#include <iostream>

int main()
{
  std::srand(std::time(nullptr));

  sf::RenderWindow window(sf::VideoMode(1280, 720), "Minecrap - 0.1",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);
  window.setPosition(sf::Vector2i(0, 0));
  window.setMouseCursorVisible(false);

  bool pressed = false, gameover = false;
  int points{}, health = 5; // maneira moderna de inicializar com 0
  float velocity = 5.f;

  sf::Font font, jet;
  font.loadFromFile("../resources/fonts/Minecraft.ttf");
  jet.loadFromFile("../resources/fonts/jetbrains.ttf");
  sf::Text score, life, gameover_text, f1;

  f1.setFont(jet);
  f1.setFillColor(sf::Color::Yellow);
  f1.setPosition(600, 10);
  f1.setString("Pressione F1 para um novo jogo.");

  // gameover
  gameover_text.setFont(font);
  gameover_text.setFillColor(sf::Color::White);
  gameover_text.setString("GAME OVER");
  gameover_text.setPosition(350, 300);
  gameover_text.setCharacterSize(100);

  // score
  score.setFont(font);
  score.setString("Pontos: " + std::to_string(points));
  score.setFillColor(sf::Color::White);
  score.setPosition(5.f, 5.f);

  // life
  life.setFont(font);
  life.setString("Vidas: " + std::to_string(health));
  life.setFillColor(sf::Color::White);
  life.setPosition(1130.f, 5.f);

  sf::Texture texture, bg, hammer;
  texture.loadFromFile("../resources/imgs/minecrap.png");
  bg.loadFromFile("../resources/imgs/fundo.jpg");
  hammer.loadFromFile("../resources/imgs/hammer.png");

  sf::Sprite object(texture), fundo(bg), ham(hammer);

  float x = static_cast<float>(std::experimental::randint(
    10, static_cast<int>(window.getSize().x - texture.getSize().x)));
  object.setPosition(x, 10.f);

  sf::Vector2i pos_mouse_win; // Posição do mouse em relação a janela(window)
  sf::Vector2f pos_mouse_coord; // Armazenará as coordenadas mapeadas

  // OBJETOS
  std::vector<sf::Sprite> objs;
  const size_t max_objs = 5;
  const float obj_vel_max = 10.f;
  float obj_vel = obj_vel_max;

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

      if (event.type == sf::Event::Resized)
      {
        sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visible_area));
      }

      if (event.type == event.MouseButtonPressed)
      {
        pressed = false;
      }

      pos_mouse_win = sf::Mouse::getPosition(window);
      pos_mouse_coord = window.mapPixelToCoords(pos_mouse_win);
      ham.setPosition(static_cast<sf::Vector2f>(pos_mouse_win));
    }

    if (gameover)
    {
      window.setMouseCursorVisible(true);
      window.clear(sf::Color::Black);
      window.draw(score);
      window.draw(f1);
      window.draw(gameover_text);
      window.display();

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
      {
        objs.clear();

        health = 5;
        points = 0;
        velocity = 5.f;

        score.setString("Pontos: " + std::to_string(points));
        life.setString("Vidas: " + std::to_string(health));

        window.setMouseCursorVisible(false);
        gameover = false;
      }
    }
    else
    {
      // CÓDIGO DO GAME
      // Adicionar objects ao nosso vector com atrasos
      if (objs.size() < max_objs)
      {
        if (obj_vel >= obj_vel_max)
        {
          x = static_cast<float>(std::experimental::randint(
            10, static_cast<int>(window.getSize().x - texture.getSize().x)));
          object.setPosition(x, 0.f);
          objs.push_back(object);
          obj_vel = 0.f;
        }
        else
        {
          obj_vel += 1.f;
        }
      }

      // Mover e deletar os objetos do vetor
      for (int i{}; i < objs.size(); ++i)
      {
        bool del = false;
        objs[i].move(0.f, velocity);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed)
        {
          if (objs[i].getGlobalBounds().contains(pos_mouse_coord))
          {
            del = true;
            points += 10.f;
            score.setString("Pontos: " + std::to_string(points));
            pressed = true;
            if (points % 100 == 0)
            {
              velocity += 0.1f;
              std::cout << "Aumentou a velocidade e agora ela é: " << velocity
                        << '\n';
            }
            if (points % 200 == 0)
            {
              ++health;
              std::cout << "Ganhou mais uma vida: " << health << '\n';
            }
          }
        }

        if (objs[i].getPosition().y > window.getSize().y)
        {
          --health;
          life.setString("Vidas: " + std::to_string(health));
          del = true;
          if (health <= 0)
          {
            std::cout << "Pontuação: " << points << '\n';
            std::cout << "GAME OVER, Vidas: " << health << '\n';
            // window.close();
            gameover = true;
          }
        }

        if (del)
        {
          objs.erase(objs.begin() + i);
        }
      }

      window.clear();
      window.draw(fundo);
      window.draw(score);
      window.draw(life);
      for (auto &e : objs)
      {
        window.draw(e);
      }
      window.draw(ham);
      window.display();
    }

  } // WHILE LOOP GAME PRINCIPAL

  // Maneira correta de deletar um ponteiro na Heap
  // delete ponteiro;
  // ponteiro = nullptr;

  return EXIT_SUCCESS;
}
