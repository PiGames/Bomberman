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

void Player::SetBombTexture(sf::Texture & texture)
{
	m_bombTexture = &texture;
}

void Player::SetBombRayTexture(sf::Texture & texture)
{
	m_bombRayTexture = &texture;
}


void Player::OnMoveKeyPressed(int x, int y)
{
	// HACK check values x,y = -1|0|1, change velocity
	const float speed = 100;
	SetVelocity(speed*x, speed*y);
}


void Player::OnActionKeyPressed()
{
	//Note: bomb position should be tile position, not player position
	m_bombs.push_back(new Bomb);
	m_bombs[m_bombs.size()]->SetBombTexture(*m_bombTexture);
	m_bombs[m_bombs.size()]->SetRayTexture(*m_bombRayTexture);
	m_bombs[m_bombs.size()]->SetDetonationTime(sf::seconds(1));
	m_bombs[m_bombs.size()]->SetRayOnScreenTime(sf::seconds(1));

	m_bombs[m_bombs.size()]->Set(sf::Vector2f(m_posX, m_posY));
}


void Player::Update(const float & dt)
{
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	m_sprite.setPosition(GetPositionX(),GetPositionY());
	
	// POSSIBLE BIG ERROR HERE (with vector)!
	for (int i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs[i]->WhatState() == Bomb::State::exploded)
		{
			delete m_bombs[i];
			m_bombs.erase(m_bombs.begin(), m_bombs.begin() + i);
		}
		else
		{
			m_bombs[i]->Update();
		}
	}
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);

	for (int i = 0; i < m_bombs.size(); i++)
	{
		target.draw(*m_bombs[i]);
	}
}
