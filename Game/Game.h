#pragma once
#include <SFML\Graphics.hpp>
#include "../Player/Player.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void start();
	void bomb();

private:
	void draw();
	void update(float);
	/*			WINDOW			*/
	sf::RenderWindow window;
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Player player;

};

