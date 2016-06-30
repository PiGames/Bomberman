#pragma once
#include<SFML\Graphics.hpp>
#include "Option.h"

class Menu
{
private:
	void optHowTo();
	void optCredits();
	// return option selected 0-4, -1 when none
	uint8_t update();

public:
	Menu();
	~Menu();
	
	// true = play, false = exit
	bool Run();

private:
	sf::RenderWindow m_window;
	Option * m_options[4];
	sf::Font * m_font;

	static const uint16_t m_SCREEN_WIDTH = 800;
	static const uint16_t m_SCREEN_HEIGHT = 600;
};

