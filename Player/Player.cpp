#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Move(int x, int y)
{
	m_sprite.move(x, y);
}
void Player::SetPosition(int x, int y)
{
	m_sprite.setPosition(x, y);
}
void Player::SetTexture()
{
	m_texture.loadFromFile("data/player.png");
	m_sprite.setTexture(m_texture);
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

float Player::getPosX()
{
	return m_sprite.getPosition().x;
}

float Player::getPosY()
{
	return m_sprite.getPosition().y;
}
