#include "Game.h"

Game::Game() :Bomb(0,0)
{
	window.create(sf::VideoMode(m_SCREEN_WIDTH, m_SCREEN_HEIGHT), "Bomberman v.0.001 - PiGames", sf::Style::Close);
	window.setFramerateLimit(60);
	player.SetTexture();
}

void Game::Start()
{
	sf::Time lastUpdate = sf::Time::Zero;
	sf::Clock time;

	elapsed = time.getElapsedTime().asSeconds();
	GetElapsedTime(elapsed);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				GenerateBomb(player.getPosX(),player.getPosY());
			}
		}
		float delta = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		update(delta);
		std::cout << "X: " << player.getPosX() << " Y: " << player.getPosY() << std::endl;
		lastUpdate = time.getElapsedTime();

		draw();
	}
}

void Game::draw()
{
	window.clear(sf::Color::White);
	Draw(window);
	player.Draw(window);
	window.display();
}
//TODO
void Game::update(float delta)
{
	float speed = 300.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.Move(-(speed *delta), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.Move(speed *delta, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.Move(0, speed *delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.Move(0, -(speed *delta));
	}
}
