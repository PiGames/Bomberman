#include "Ray.h"



void Ray::draw(sf::RenderWindow & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

Ray::Ray()
{
}


Ray::~Ray()
{
}

bool Ray::Contains(sf::FloatRect & floatRect)
{
	if (m_sprite.getGlobalBounds().intersects(floatRect))
	{
		return true;
	}

	return false;
}

void Ray::SetTexture(sf::Texture & texture)
{
	m_texture = &texture;
}
