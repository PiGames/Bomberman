#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();
	void Run();

private:
	void draw();
	void processEvents();

	Button* m_buttonsPointers[1];

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_pigamesLogoTexture;
	sf::Sprite m_pigamesLogoSprite;

	sf::RenderWindow* m_window;

	bool m_exit;


};

