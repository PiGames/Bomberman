#include "Ray.h"


Ray::Ray(Side side)
	:m_side(side)
{
	
}


Ray::~Ray()
{
}

bool Ray::Contains(sf::FloatRect & floatRect)
{
	return false;
}

void Ray::SetTexture(sf::Texture & texture)
{
	m_texture = &texture;
	m_sprite.setTexture(*m_texture);
}

int Ray::GetSide()
{
	return m_side;
}

void Ray::SetSize(unsigned short size)
{
	m_size = size;
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size*TILE_SIZE,TILE_SIZE));//ustaw rozmiar tekstury w zale¿noœci od d³ugoœci promienia
	m_sprite.setOrigin(0, m_sprite.getGlobalBounds().height / 2.f);
	switch (m_side)
	{
	case Ray::Up:
		m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y - TILE_SIZE/2);//przesuñ o pó³ kafla
		m_sprite.setRotation(270);// ustaw rotacje w zale¿noœci od strony w któr¹ idzie wybuch
		break;
	case Ray::Down:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + TILE_SIZE/2);
		m_sprite.setRotation(90);
		break;
	case Ray::Left:
		m_sprite.setPosition(m_sprite.getPosition().x - TILE_SIZE/2, m_sprite.getPosition().y );
		m_sprite.setRotation(180);
		break;
	case Ray::Right:
		m_sprite.setPosition(m_sprite.getPosition().x + TILE_SIZE/2, m_sprite.getPosition().y);
		
		break;
	default:
		break;
	}


	
}

void Ray::SetPosition(float x, float y)
{
	m_sprite.setPosition(x,y);
}

sf::Drawable & Ray::GetSprite()
{
	return m_sprite;
}

