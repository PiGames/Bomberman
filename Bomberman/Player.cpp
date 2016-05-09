#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}


void Player::SetTexture(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
	m_physicalBody.SetSize(texture.getSize().x, texture.getSize().y);
}


void Player::OnMoveKeyPressed(int x, int y)
{
	// HACK check values x,y = -1|0|1, change velocity
	const float speed = 100;
	m_physicalBody.SetVelocity(speed*x, speed*y);
}


void Player::OnActionKeyPressed()
{
	// HACK plant the bomb
}


void Player::Update(const float & dt)
{
	m_physicalBody.Update(dt);
	m_sprite.setPosition(m_physicalBody.GetPositionX(), m_physicalBody.GetPositionY());
}


PhysicalBody & Player::GetPhysicalBody()
{
	return m_physicalBody;
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
