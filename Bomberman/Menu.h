#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Game.h"
#include "Slider.h"

class Menu
{
private:
	void options();

public:
	Menu(size_t width, size_t height);
	~Menu();
	void Run();

private:
	Game* m_game;

	void draw();
	void processEvents();

	Button* m_buttonsPointers[4];
	Button* m_optionReturnButton;

	Slider* m_playersSlider;
	Slider* m_volumeSlider;

	float playersLives, volume;
	sf::Text optionsText[4];
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

	size_t m_windowHeight;
	size_t m_windowWidth;

	sf::Music m_music;

	bool m_credits;
	sf::Sprite m_creditsSprite;
	sf::Texture m_creditsTexture;

	bool m_options;

};
