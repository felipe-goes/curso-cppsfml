#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(1280, 720), "Spaceship 1.0",
    sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(0, 0));
  window->setFramerateLimit(60);

  // spaceship
  std::shared_ptr<sf::Texture> spaceship_texture =
    std::make_shared<sf::Texture>();
  spaceship_texture->loadFromFile("./resources/imgs/spaceship-min.png");
  std::shared_ptr<sf::Sprite> spaceship = std::make_shared<sf::Sprite>();
  spaceship->setTexture(*spaceship_texture);
  spaceship->setPosition(0, 0);

  // bullet
  auto bullet_texture = std::make_shared<sf::Texture>();
  bullet_texture->loadFromFile("./resources/imgs/bullet.png");
  auto bullet = std::make_shared<sf::Sprite>(*bullet_texture);
  std::vector<sf::Sprite> bullets;
  int shoot = 20;

  // background
  auto bg_texture = std::make_shared<sf::Texture>();
  bg_texture->loadFromFile("./resources/imgs/bg.jpg");
  auto bg = std::make_shared<sf::Sprite>(*bg_texture);

  while (window->isOpen())
  {
    sf::Event event;
    while (window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window->close();
      }
    }

    // Movimenta a spaceship com as teclas direcionais
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      spaceship->move(10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      spaceship->move(-10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      spaceship->move(0.f, 10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      spaceship->move(0.f, -10.f);
    }

    // Verifica se a nave(spaceship) ultrapassou os limites da janela
    if (spaceship->getPosition().x < 0)
    {
      spaceship->setPosition(0, spaceship->getPosition().y);
    }
    if (spaceship->getPosition().x >
        window->getSize().x - spaceship_texture->getSize().x)
    {
      spaceship->setPosition(window->getSize().x -
                               spaceship_texture->getSize().x,
                             spaceship->getPosition().y);
    }
    if (spaceship->getPosition().y < 0)
    {
      spaceship->setPosition(spaceship->getPosition().x, 0);
    }
    if (spaceship->getPosition().y >
        window->getSize().y - spaceship_texture->getSize().y)
    {
      spaceship->setPosition(spaceship->getPosition().x,
                             window->getSize().y -
                               spaceship_texture->getSize().y);
    }

    // BULLET

    if (shoot < 20)
    {
      shoot++;
    }
    // Quando pressionar a tecla de espaço adiciona um bullet
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shoot >= 20)
    {
      bullet->setPosition(spaceship->getPosition().x + 35.f,
                          spaceship->getPosition().y +
                            spaceship_texture->getSize().y / 2.f - 5.f);
      bullets.push_back(*bullet);
      shoot = 0;
    }

    // Mover e deletar caso ultrapasse os limites da janela
    for (int i{}; i < bullets.size(); ++i)
    {
      bullets[i].move(60.f, 0.f);
      if (bullets[i].getPosition().x > window->getSize().x)
      {
        bullets.erase(bullets.begin() + i);
      }
    }

    window->clear();
    window->draw(*bg);
    window->draw(*spaceship);
    for(auto &b : bullets)
    {
      window->draw(b);
    }
    window->display();
  }

  return EXIT_SUCCESS;
}
