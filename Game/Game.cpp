#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bomberman v.0.001 - PiGames", sf::Style::Close);
}


Game::~Game()
{
}

void Game::start()
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

void Game::bomb()
{
}

void Game::draw()
{
	window.clear(sf::Color::White);
	player.draw(window);
	window.display();
}
//TODO
void Game::update(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-5 , 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(5, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		bomb();
	}
}
