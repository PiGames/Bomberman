#pragma once
#include <SFML\Graphics.hpp>
#include "../Player/Player.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void Start();
	void Bomb();

private:
	void draw();
	void update(float);
	/*			WINDOW			*/
	sf::RenderWindow window;
	const int m_SCREEN_WIDTH = 1024;
	const int m_SCREEN_HEIGHT = 768;

	Player player;

};

