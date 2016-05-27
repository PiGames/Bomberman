#include "Player.h"



Player::Player()
{
	
}


Player::~Player()
{
}


void Player::SetAnimator(Animator& animator, size_t width, size_t height)
{
	float w = static_cast<float>(width);
	float h = static_cast<float>(height);

	float tileSize = 64; // HACK tmp only

	m_sprite.setOrigin(w / 2.f, h / 2.f);// TODO fix collision
	SetSize(w, h);
	
	m_animator = &animator;
	m_animator->SetSprite(m_sprite);

	SetPositionX(3 * tileSize + w); 
	SetPositionY(5 * tileSize + h);
	m_sprite.setPosition(sf::Vector2f(3 * tileSize + w, 5 * tileSize + h));

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
