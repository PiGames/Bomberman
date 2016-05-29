#include "Bomb.h"


Bomb::Bomb()
	:m_state(State::waitingForExplosion)
{
	m_detonationClock.restart();
	m_rays.resize(4);
}


Bomb::~Bomb()
{
	for (int i = 0; i < m_rays.size(); i++)
		delete m_rays[i];
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

Bomb::State Bomb::GetState()
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
	x = m_positionInTilesCoordsX = x / TILE_SIZE; 
	y = m_positionInTilesCoordsY = y / TILE_SIZE;

	SetPositionX(x*TILE_SIZE + TILE_SIZE/2);
	SetPositionY(y*TILE_SIZE + TILE_SIZE/2);

}

void Bomb::SetLevelPointer(Level & level)
{
	this->level = &level;
}

void Bomb::Update()
{	
	m_sprite.setPosition(GetPositionX(), GetPositionY());

	if (m_detonationClock.getElapsedTime() >= m_detonationTime && m_state < State::exploding)
	{
		m_state = State::exploding;
		explode();
	}
	else if (m_detonationClock.getElapsedTime() >= m_detonationTime + m_rayOnScreenTime && m_state < State::exploded)
	{
		m_state = State::exploded;

		for each (std::pair<int,int> var in m_tilesToDeleteAfterExplosion)
			level->DestroyTile(var.first, var.second);
	}
}

void Bomb::explode()
{
	
	for (int i = 0; i < m_rays.size(); i++)
	{
		m_rays[i] = new Ray(static_cast<Ray::Side>(i));

		m_rays[i]->SetTexture(*m_rayTexture);
		m_rays[i]->SetPosition(m_positionInTilesCoordsX*TILE_SIZE+TILE_SIZE/2.f, m_positionInTilesCoordsY*TILE_SIZE + TILE_SIZE / 2.f);
		m_rays[i]->SetSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
	}
}

unsigned short Bomb::getRaySizeAfterCollisions(Ray::Side side)
{
	unsigned short size = 0;

	switch (side)
	{
	case Ray::Up:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (m_positionInTilesCoordsY - i >= 0 && level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY - i) == TT::TileType::NONE)
				size=i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsY - size - 1 > 0 && level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY - size - 1) == TT::TileType::WEAK_WALL)
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX, m_positionInTilesCoordsY - ++size));
	
		break;
	case Ray::Down:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (m_positionInTilesCoordsY + i < level->GetHeight() && level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY + i) == TT::TileType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsY + size + 1 < level->GetHeight() && level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY + size + 1) == TT::TileType::WEAK_WALL)
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX, m_positionInTilesCoordsY + ++size));
		break;
	case Ray::Left:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (m_positionInTilesCoordsX - i >= 0 && level->GetTile(m_positionInTilesCoordsX - i, m_positionInTilesCoordsY) == TT::TileType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsX - size - 1 > 0 && level->GetTile(m_positionInTilesCoordsX - size - 1, m_positionInTilesCoordsY) == TT::TileType::WEAK_WALL)
		{	
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX - ++size, m_positionInTilesCoordsY));
		}
		break;
	case Ray::Right:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (m_positionInTilesCoordsX + i  < level->GetWidth() && level->GetTile(m_positionInTilesCoordsX + i, m_positionInTilesCoordsY) == TT::TileType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsX + size + 1 < level->GetWidth() && level->GetTile(m_positionInTilesCoordsX + size + 1, m_positionInTilesCoordsY) == TT::TileType::WEAK_WALL)
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX + ++size, m_positionInTilesCoordsY));

		break;
	default:
		break;
	}

	
	return size;
}

void Bomb::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(m_state == State::waitingForExplosion)
	target.draw(m_sprite);
	else
	{
		for (int i = 0; i < m_rays.size(); ++i)
		{
			target.draw(m_rays[i]->GetSprite());
		}
	}
}
