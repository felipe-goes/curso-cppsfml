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

  int points{}, health = 5; // maneira moderna de inicializar com 0

  sf::Font font;
  font.loadFromFile("../resources/fonts/Minecraft.ttf");
  sf::Text score, life;

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

  sf::Texture texture, bg;
  texture.loadFromFile("../resources/imgs/minecrap.png");
  bg.loadFromFile("../resources/imgs/fundo.jpg");

  sf::Sprite object(texture), fundo(bg);

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

      pos_mouse_win = sf::Mouse::getPosition(window);
      pos_mouse_coord = window.mapPixelToCoords(pos_mouse_win);
    }

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
      objs[i].move(0.f, 5.f);

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        if (objs[i].getGlobalBounds().contains(pos_mouse_coord))
        {
          del = true;
          points += 10.f;
          score.setString("Pontos: " + std::to_string(points));
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
          window.close();
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
    window.display();
  }

  // Maneira correta de deletar um ponteiro na Heap
  // delete ponteiro;
  // ponteiro = nullptr;

  return EXIT_SUCCESS;
}
