#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Button
{
public:
	Button(sf::Vector2f position, sf::Vector2i size, std::string pressTexture_src, std::string unpressTexture_src, std::string text);
	~Button();

	bool Check(sf::Vector2i mousePosition);

	void Update(sf::Vector2i mousePosition, bool buttonPressed);

	void DoAction();

	sf::Sprite* GetSpritePointer();
	sf::Text* GetTextPointer();

	sf::Vector2f m_position;
	sf::Vector2i m_size;

private:

	sf::Texture m_pressTexture;
	sf::Texture m_unpressTexture;

	sf::Sprite m_pressSprite;
	sf::Sprite m_unpressSprite;

	sf::Font m_font;
	sf::Text m_text;

	bool m_press = false;


};

