#include "Bomb.h"



void Bomb::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_state == State::exploding)
	{
		for (short i = 0; i < m_rays.size(); i++)
		{
			target.draw(m_rays[i]);
		}
	}

	if (m_state == State::waitingForExplosion)
	{
		target.draw(m_sprite);
	}
}

Bomb::Bomb()
{
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
	if (m_state == State::exploding)
	{
		for (short i = 0; i < m_rays.size(); i++)
		{
			if (m_rays[i].Contains(floatRect))
			{
				return true;
			}
		}
	}

	return false;
}

Bomb::State Bomb::WhatState()
{
	return m_state;
}

void Bomb::SetBombTexture(sf::Texture & texture)
{
	m_bombTexture = &texture;
}

void Bomb::SetRayTexture(sf::Texture & texture)
{
	m_rayTexture = &texture;
}

void Bomb::Set(sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void Bomb::Update()
{
	if (m_state == State::waitingForExplosion)
	{
		if (m_detonationClock.getElapsedTime() >= m_detonationTime)
		{
			m_state = State::exploding;
			m_detonationClock.restart();
		}
	}

	else if (m_state == State::exploding)
	{
		if (m_detonationClock.getElapsedTime() >= m_rayOnScreenTime)
		{
			m_state = State::exploded;
		}
	}
}
