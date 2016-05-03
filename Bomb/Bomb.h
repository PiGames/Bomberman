#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Bomb
{
public:
	Bomb(int ,int);
	~Bomb();

	void GenerateBomb(int, int);
	void Draw(sf::RenderWindow&);
	void GetElapsedTime(float&);

private:
	sf::Sprite m_bomb_sprite;
	sf::Texture m_texture;
	std::vector <Bomb*> m_bomb;

	sf::Sprite getSprite();
	float elapsedTime;

	void loadBombTexture();
	void explosion();
};
