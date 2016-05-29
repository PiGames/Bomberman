#include "Player.h"



Player::Player()
	:m_bomb(nullptr)
{
	
}


Player::~Player()
{
}


void Player::SetTexture(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
	SetPositionX(3 * TILE_SIZE+ TILE_SIZE/2);
	SetPositionY(5 * TILE_SIZE + TILE_SIZE/2);
	m_sprite.setPosition(sf::Vector2f(3 * TILE_SIZE + TILE_SIZE/2, 5 * TILE_SIZE + TILE_SIZE/2));
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
	const float speed = 120;
	SetVelocity(speed*x, speed*y);
}


void Player::TryPlantingTheBomb()
{
	if(m_bomb==nullptr)
	{
		m_bomb = new Bomb();
		m_bomb->SetBombTexture(*m_bombTexture);
		m_bomb->SetRayTexture(*m_bombRayTexture);
		m_bomb->SetDetonationTime(sf::seconds(1));
		m_bomb->SetRayOnScreenTime(sf::seconds(1));
		m_bomb->SetPosition(GetPositionX(), GetPositionY());
		m_bomb->SetLevelPointer(*level);
	}
}

void Player::SetLevelPointer(Level & level)
{
	this->level = &level;
}



void Player::Update(const float & dt)
{
	if (movementX != 0 && movementY != 0)
	{
		movementX /= 1.41f;
		movementY /= 1.41f;
	}
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	m_sprite.setPosition(GetPositionX(),GetPositionY());

	if (m_bomb != nullptr)
	{
		m_bomb->Update();

		if (m_bomb->GetState() == Bomb::exploded)
		{
			delete m_bomb;
			m_bomb = nullptr;
		}
	}

	
}


void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_bomb != nullptr)
		target.draw(*m_bomb);

	target.draw(m_sprite);
}
