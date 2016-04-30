#pragma once
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player();
	~Player();

	void move(int, int);
	void setPosition(int, int);
	void setTexture();
	void draw(sf::RenderWindow &);

	float getPosX();
	float getPosY();

protected:
	sf::Texture texture;
	sf::Sprite sprite;
};

