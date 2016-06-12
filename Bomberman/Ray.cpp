#include "Ray.h"


void Ray::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

Ray::Ray(Side side)
	:m_side(side)
{
	
}


Ray::~Ray()
{
}

void Ray::SetAnimator(Animator & animator)
{
	m_animator = &animator;
	m_animator->SetSprite(m_sprite);
	m_animator->SetDelayBetweenFrames(0.1f);
	m_animator->ChangeActiveState("explosion");
}

int Ray::GetSide()
{
	return m_side;
}

void Ray::SetRaySpriteSize(unsigned short size)
{
	m_size = size;
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size*TILE_SIZE,TILE_SIZE));
	m_sprite.setOrigin(0, m_sprite.getGlobalBounds().height / 2.f);
	switch (m_side)
	{
	case Ray::Up:
		m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y - TILE_SIZE/2);
		m_sprite.setRotation(270);
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

	SetSize(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	SetPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

void Ray::SetPosition(float x, float y)
{
	m_sprite.setPosition(x,y);
}

void Ray::Update(const float & dt)
{
	m_animator->Animate(dt);
}

