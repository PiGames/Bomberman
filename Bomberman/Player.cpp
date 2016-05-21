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
	SetSize(texture.getSize().x, texture.getSize().y);

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
	SetPositionX(3 * 64 + 32);
	SetPositionY(5 * 64 + 32);
	m_sprite.setPosition(sf::Vector2f(3 * 64 + 32, 5 * 64 + 32));

}


void Player::OnMoveKeyPressed(int x, int y)
{
	// HACK check values x,y = -1|0|1, change velocity
	const float speed = 100;
	SetVelocity(speed*x, speed*y);
}


void Player::OnActionKeyPressed()
{
	// HACK plant the bomb
}


void Player::Update(const float & dt)
{
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	m_sprite.setPosition(GetPositionX(),GetPositionY());
	
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
