#pragma once
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player();
	~Player();

	void Move(int, int);
	void SetPosition(int, int);
	void SetTexture();
	void Draw(sf::RenderWindow &);

	float getPosX();
	float getPosY();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

