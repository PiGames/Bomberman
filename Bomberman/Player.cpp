#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{
}


void Player::SetAnimator(Animator& animator)
{
	m_sprite.setOrigin(32.f / 2.f, 32.f / 2.f);// TODO fix collision
	
	m_animator = &animator;
	m_animator->SetSprite(m_sprite);

	SetPositionX(3 * 64 + 32); 
	SetPositionY(5 * 64 + 32);
	m_sprite.setPosition(sf::Vector2f(3 * 64 + 32, 5 * 64 + 32));

}


void Player::OnMoveKeyPressed(int x, int y)
{
	const float speed = 100;
	SetVelocity(speed*x, speed*y);
}


void Player::OnActionKeyPressed()
{
	// HACK plant the bomb
}


void Player::Update(const float & dt)
{
	m_animator->Animate(dt);
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	m_sprite.setPosition(GetPositionX(),GetPositionY());
	
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
