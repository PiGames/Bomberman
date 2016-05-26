#include "Bomb.h"



Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

void Bomb::SetTexture(sf::Texture & texture)
{
	m_texture = &texture;
}

void Bomb::put(sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}
