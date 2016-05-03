#pragma once
#include <SFML\Graphics.hpp>
#include "../Player/Player.h"
#include "../Bomb/Bomb.h"
#include <iostream>

class Game :public Bomb
{
public:
	Game();
	float elapsed;
	void Start();
private:
	void draw();
	void update(float);
	/*			WINDOW			*/
	sf::RenderWindow window;
	const int m_SCREEN_WIDTH = 1024;
	const int m_SCREEN_HEIGHT = 768;

	Player player;
};

