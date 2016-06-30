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

	Button* m_buttonsPointers[3];

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_pigamesLogoTexture;
	sf::Sprite m_pigamesLogoSprite;

	sf::Texture m_gameLogoTexture;
	sf::Sprite m_gameLogoSprite;

	sf::Font m_font;
	sf::Text m_gameVersion;

	sf::RenderWindow* m_window;

	bool m_exit;


};

