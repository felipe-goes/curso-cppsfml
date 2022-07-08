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
  bullet->setColor(sf::Color::Red);
  bool move_bullet = false;

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

    // Movimento da nave
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      move_bullet = true;
    }

    // Colisão com as bordas da tela
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

    if (!move_bullet)
    {
      bullet->setPosition(spaceship->getPosition().x + 35.f,
                          spaceship->getPosition().y +
                            spaceship_texture->getSize().y / 2.f - 5.f);
    }
    else
    {
      bullet->move(20.f, 0.f);
      if (bullet->getPosition().x > window->getSize().x - bullet_texture->getSize().x)
      {
        move_bullet = false;
      }
    }

    window->clear();
    window->draw(*spaceship);
    window->draw(*bullet);
    window->display();
  }

  return EXIT_SUCCESS;
}
