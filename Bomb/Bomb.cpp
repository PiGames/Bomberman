#include "Bomb.h"



Bomb::Bomb(int x = 0, int y = 0)
{
	loadBombTexture();
	m_bomb_sprite.setPosition(x, y);
}

Bomb::~Bomb()
{
}

void Bomb::GenerateBomb(int x, int y)
{
	Bomb* plant = new Bomb(x,y);
	m_bomb.push_back(plant);
	std::cout << "Bomb planted at: " << x << " " << y << std::endl;
}

void Bomb::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < m_bomb.size(); i++)
		window.draw(m_bomb[i]->getSprite());
}
//TODO
void Bomb::loadBombTexture()
{
	if (!m_texture.loadFromFile("data/bomb.png"))
		std::cout << "COULD NOT LOADED BOMB TEXTURE!" << std::endl;
	m_bomb_sprite.setTexture(m_texture);
}
//TODO
void Bomb::explosion()
{
	/*if (!m_texture.loadFromFile(""))
		std::cout << "COULD NOT LOADED EXPLOSION TEXTURE!" << std::endl;
	m_bomb_sprite.setTexture(m_texture);*/
}

sf::Sprite Bomb::getSprite()
{
	return m_bomb_sprite;
}

void Bomb::GetElapsedTime(float &time)
{
	time = elapsedTime;
}
