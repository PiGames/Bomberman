#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(m_SCREEN_WIDTH, m_SCREEN_HEIGHT), "Bomberman v.0.001 - PiGames", sf::Style::Close);
}


Game::~Game()
{
}

void Game::Start()
{

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
		std::cout << player.getPosX() << " Y: " << player.getPosY() << std::endl;
		draw();
	}

void Game::Bomb()
{
}

void Game::draw()
{
	window.clear(sf::Color::White);
	player.Draw(window);
	window.display();
}
//TODO
void Game::update(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.Move(-5 , 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.Move(5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.Move(0, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.Move(0, -5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Bomb();
	}
}
