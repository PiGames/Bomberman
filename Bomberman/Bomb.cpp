#include "Bomb.h"



void Bomb::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

Bomb::Bomb()
	:m_state(State::waitingForExplosion)
{
	m_detonationClock.restart();
}


Bomb::~Bomb()
{
}

void Bomb::SetDetonationTime(sf::Time & time)
{
	m_detonationTime = time;
}

void Bomb::SetRayOnScreenTime(sf::Time & time)
{
	m_rayOnScreenTime = time;
}

bool Bomb::IsObjectInRay(sf::FloatRect & floatRect)
{
	return false;
}

Bomb::State Bomb::WhatState()
{
	return m_state;
}

void Bomb::SetBombTexture(sf::Texture & texture)
{
	m_bombTexture = &texture;
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}

void Bomb::SetRayTexture(sf::Texture & texture)
{
	m_rayTexture = &texture;
}

void Bomb::SetPosition(int x, int y)
{	
	//TODO it should depend on actual TILE_SIZE
	x = m_positionInTilesCoordsX = x / TILE_SIZE; 
	y = m_positionInTilesCoordsY = y / TILE_SIZE;

	SetPositionX(x*TILE_SIZE + TILE_SIZE/2);
	SetPositionY(y*TILE_SIZE + TILE_SIZE/2);

}

void Bomb::Update()
{	
	//TODO it can be done better
	m_sprite.setPosition(GetPositionX(), GetPositionY());

	if (m_detonationClock.getElapsedTime() >= m_detonationTime && m_state < State::exploding)
	{
		m_state = State::exploding;
		explode();
	}
	else if (m_detonationClock.getElapsedTime() >= m_detonationTime + m_rayOnScreenTime && m_state<State::exploded)
		m_state = State::exploded;
	

	
	
}

void Bomb::explode()
{
	for (int i = 0; i < m_rays.size(); i++)
	{
		m_rays[i] = new Ray(static_cast<Ray::Side>(i));

		

	}
}
