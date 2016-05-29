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
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}

int Ray::GetSide()
{
	return m_side;
}

void Ray::SetSize(unsigned short size)
{
	m_size = size;
	switch (m_side)
	{
	case Ray::Up:
		m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y - TILE_SIZE);
		m_sprite.setTextureRect(sf::IntRect(TILE_SIZE, m_size*TILE_SIZE,-TILE_SIZE, -m_size*TILE_SIZE));
		break;
	case Ray::Down:
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + TILE_SIZE);
		m_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, m_size*TILE_SIZE));
		break;
	case Ray::Left:
		m_sprite.setPosition(m_sprite.getPosition().x - TILE_SIZE, m_sprite.getPosition().y );
		m_sprite.setTextureRect(sf::IntRect(m_size* TILE_SIZE, TILE_SIZE, -m_size* TILE_SIZE, TILE_SIZE));
		break;
	case Ray::Right:
		m_sprite.setPosition(m_sprite.getPosition().x + TILE_SIZE, m_sprite.getPosition().y);
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_size*TILE_SIZE, TILE_SIZE));
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

