#include <SFML/Graphics.hpp>

const int H = 23, W = 80; // tiramos a divisão por conta do offset
float offset_x = 0.f, offset_y = 0.f;

sf::String tilemap[H] = {
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B          0                     B                                       B     B",
"B                                B                                       B     B",
"B                                B                                       B     B",
"B        BBBB                    B                                       B     B",
"B                                B                                       B     B",
"B                   BBBBB      0 B                                       B     B",
"B                                B                                       B     B",
"B         0 0 0 0             BBBB                0000                BBBB     B",
"B                                B                                       B     B",
"BBB                              B       BB                              B     B",
"B              BB                BB    BB              BB              BBBB    B",
"B        0     BB         BB           BB              BB                      B",
"B    B         BB         BB           BB    B         BB         BB           B",
"B    B         BB    0    BB           BB    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

class Player
{
public:
  const int ground = 736 - (82 + 32);
  float dx, dy, frame;
  bool on_ground;
  sf::FloatRect rect;
  sf::Sprite sprite;

  Player(sf::Texture &texture)
  {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 43, 82));
    rect = sf::FloatRect(64, ground, 43, 82);
    dx = 0.1f;
    dy = 0.1f;
    frame = 0.f;
    on_ground = false;
  }

  void update(float time)
  {
    // PULO/GRAVIDADE
    // Para usar no setPosition
    rect.left += dx * time;
    collision(1);
    rect.top += dy * time;

    if (!on_ground)
    {
      dy = dy + 0.0006f * time;
      sprite.move(sprite.getPosition().x, dy);
    }

    on_ground = false; // Para ele não ficar voando
    collision(0);

    if (rect.top > ground) // Para ele não passar do chão
    {
      rect.top = ground;
      dy = 0;
      on_ground = true;
    }

    frame += 0.3f * time;
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

    sprite.setPosition(rect.left - offset_x,
                       rect.top - offset_y); // dx e o dy os de movimento verdadeiros foram
                                  // armazenados em rect.left e rect.top
    dx = 0; // Para ele movimentar a cada vez que a gente teclar as setas, caso
            // contrário ele ficará andando sequencialmente
  }

  void collision(int direction)
  {
    for (size_t i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
    {
      for (size_t j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
      {
        if (tilemap[i][j] == 'B')
        {
          // PARA o X
          if (direction == 1)
          {
            if (dx > 0)
            {
              rect.left = j * 32 - rect.width;
            }
            if (dx < 0)
            {
              rect.left = j * 32 + 32;
            }
          }
          // PARA o Y
          if (direction == 0)
          {
            if (dy > 0)
            {
              rect.top = i * 32 - rect.height;
              dy = 0;
              on_ground = true;
            }
            if (dy < 0)
            {
              rect.top = i * 32 + 32;
              dy = 0;
            }
          }
        }

        if (tilemap[i][j] == '0')
        {
          tilemap[i][j] = ' ';
        }

      }
    }
  }

};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 736), "Plataforma 2D",
                          sf::Style::Close | sf::Style::Titlebar);
  window.setPosition(sf::Vector2i(0, 0));

  const float height_floor = 32.f, speed = 0.4f;

  sf::Texture texture, floor_texture, bg_texture;
  texture.loadFromFile("./resources/imgs/afro.png");
  floor_texture.loadFromFile("./resources/imgs/floormax.jpg");
  bg_texture.loadFromFile("./resources/imgs/bg.jpg");
  sf::Sprite floor(floor_texture), bg(bg_texture);

  // floor
  floor.setPosition(0.f, window.getSize().y - height_floor);

  sf::RectangleShape rectangle(sf::Vector2f(height_floor, height_floor));

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

    // TODO: remover espaço final do offset
    if (player.rect.left > (float)window.getSize().x/2.f)
    {
      offset_x = player.rect.left - window.getSize().x / 2.f;
    }
    if (player.rect.top < (float)window.getSize().y/2.f)
    {
      offset_y = player.rect.top - window.getSize().y / 2.f;
    }

    window.clear(sf::Color::Yellow);
    window.draw(bg);

    for (size_t i{}; i < H; i++)
    {
      for (size_t j{}; j < W; j++)
      {
        if (tilemap[i][j] == 'B')
        {
          rectangle.setFillColor(sf::Color::Black);
        }
        if (tilemap[i][j] == '0')
        {
          rectangle.setFillColor(sf::Color::Blue);
        }
        if (tilemap[i][j] == ' ')
        {
          continue;
        }

        rectangle.setPosition(j * 32 - offset_x, i * 32 - offset_y);
        window.draw(rectangle);
      }
    }

    window.draw(floor);
    window.draw(player.sprite);
    window.display();
  }

  return EXIT_SUCCESS;
}
