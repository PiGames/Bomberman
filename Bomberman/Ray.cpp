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
}

int Ray::GetSide()
{
	return m_side;
}

void Ray::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

