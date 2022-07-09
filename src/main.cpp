#include <SFML/Graphics.hpp>

class Player
{
public:
  const int ground = 720 - (82 + 100);
  float dx, dy, frame;
  bool on_ground;
  sf::FloatRect rect;
  sf::Sprite sprite;

  Player(sf::Texture &texture)
  {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 43, 82));
    rect = sf::FloatRect(0, ground, 43, 82);
    dx = 0.f;
    dy = 0.f;
    frame = 0.f;
    on_ground = false;
  }

  void update(float time)
  {
    // PULO/GRAVIDADE
    // Para usar no setPosition
    rect.left += dx * time;
    rect.top += dy * time;

    if (!on_ground)
    {
      dy = dy + 0.0006f * time;
      sprite.move(sprite.getPosition().x, dy);
    }

    on_ground = false; // Para ele não ficar voando

    if (rect.top > ground) // Para ele não passar do chão
    {
      rect.top = ground;
      dy = 0;
      on_ground = true;
    }

    frame += 0.5f * time;
    if (frame > 6.f)
    {
      frame -= 6.f;
    }

    // Para utilizar os frames(7) para a direita
    if (dx > 0)
    {
      sprite.setTextureRect(sf::IntRect(43 * (int)frame, 0, 43, 82));
    }
    // Para utilizar os frames(7) para a esquerda
    if (dx < 0)
    {
      sprite.setTextureRect(sf::IntRect(43 * (int)frame + 43, 0, -43, 82));
    }

    sprite.setPosition(rect.left,
                       rect.top); // dx e o dy os de movimento verdadeiros foram
                                  // armazenados em rect.left e rect.top
    dx = 0; // Para ele movimentar a cada vez que a gente teclar as setas, caso
            // contrário ele ficará andando sequencialmente
  }
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Plataforma 2D",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(0, 0));

  const float height_floor = 100.f, speed = 0.4f;

  sf::Texture texture, floor_texture, bg_texture;
  texture.loadFromFile("./resources/imgs/afro.png");
  floor_texture.loadFromFile("./resources/imgs/floormax.jpg");
  bg_texture.loadFromFile("./resources/imgs/bg.jpg");
  sf::Sprite floor(floor_texture), bg(bg_texture);

  // floor
  floor.setPosition(0.f, window.getSize().y - height_floor);

  Player player(texture);

  // pulo/gravidade
  sf::Clock clock;

  while (window.isOpen())
  {
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 800;

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      player.dx = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      player.dx = -speed;
    }

    // Quando pressionarmos a tecla para cima ele pulará
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      if (player.on_ground)
      {
        player.dy = -speed;
      }
    }

    player.update(time);

    window.clear(sf::Color::Yellow);
    window.draw(bg);
    window.draw(floor);
    window.draw(player.sprite);
    window.display();
  }

  return EXIT_SUCCESS;
}
