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
	m_sprite.getTexture();
	switch (m_side)
	{
	case Ray::Up:
		m_sprite.setPosition(m_sprite.getPosition().x,m_sprite.getPosition().y - TILE_SIZE/2);
		m_sprite.setRotation(270);
		SetSize(TILE_SIZE, TILE_SIZE*size + TILE_SIZE);
		SetPositionY(static_cast<int>(GetPositionY() / TILE_SIZE) * TILE_SIZE);
		PhysicalBody::SetPositionY(GetPositionY()- ((TILE_SIZE*size) + TILE_SIZE)/2 + TILE_SIZE);
		break;
	case Ray::Down:
		SetPositionY(static_cast<int>(GetPositionY() / TILE_SIZE) * TILE_SIZE);
		m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + TILE_SIZE/2);
		m_sprite.setRotation(90);
		SetSize(TILE_SIZE, TILE_SIZE*size);
		PhysicalBody::SetPositionY(GetPositionY() +TILE_SIZE + (TILE_SIZE*size) / 2 );
		break;
	case Ray::Left:
		SetPositionX(static_cast<int>(GetPositionX() / TILE_SIZE) * TILE_SIZE);
		m_sprite.setPosition(m_sprite.getPosition().x - TILE_SIZE/2, m_sprite.getPosition().y );
		m_sprite.setRotation(180);
		SetSize(TILE_SIZE*size, TILE_SIZE);
		PhysicalBody::SetPositionX(GetPositionX() - (TILE_SIZE*size) / 2);
		break;
	case Ray::Right:
		SetPositionX(static_cast<int>(GetPositionX() / TILE_SIZE) * TILE_SIZE);
		m_sprite.setPosition(m_sprite.getPosition().x + TILE_SIZE/2, m_sprite.getPosition().y);
		SetSize(TILE_SIZE*size, TILE_SIZE);
		PhysicalBody::SetPositionX(GetPositionX() +TILE_SIZE + (TILE_SIZE*size) / 2);
		break;
	default:
		break;
	}

}

void Ray::SetPosition(float x, float y)
{
	m_sprite.setPosition(x,y);
	PhysicalBody::SetPositionX(x);
	PhysicalBody::SetPositionY(y);
}

void Ray::Update(float dt)
{

}

