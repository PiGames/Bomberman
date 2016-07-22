#include "Bomb.h"


Bomb::Bomb(bool setColor)
	:m_state(State::waitingForExplosion),
	m_isMoving(false)
{
	m_detonationClock.restart();
	m_rays.resize(4);

	if (!m_soundBuffer.loadFromFile("data/expl.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'data/expl.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}

	m_explosionSound.setBuffer(m_soundBuffer);

  if (setColor)
		m_sprite.setColor(sf::Color(243, 197, 48));
}


Bomb::~Bomb()
{
	for (unsigned int i = 0; i < m_rays.size(); i++)
		delete m_rays[i];

	delete m_animator;
}

void Bomb::SetAnimator(Animator & animator, size_t width, size_t height)
{
	float w = static_cast<float>(width);
	float h = static_cast<float>(height);

	float tileSize = 64; // HACK tmp only
	m_animator = &animator;
	m_animator->SetSprite(m_sprite);
	m_animator->SetDelayBetweenFrames(1.f);
	m_animator->ChangeActiveState("waitingForExplosion");
	m_sprite.setOrigin(w / 2.f, h / 2.f);
}

void Bomb::SetDetonationTime(sf::Time time)
{
	m_detonationTime = time;
}

void Bomb::SetRayOnScreenTime(sf::Time time)
{
	m_rayOnScreenTime = time;
}

bool Bomb::IsObjectInRay(PhysicalBody & physicalBody)
{
	if (m_rays[0] != nullptr)
	{
		if (m_state == exploding)
		{
			if (IsCollision(*this))
			{
				return true;
			}
		}

		for (unsigned int i = 0; i < m_rays.size(); i++)
		{
			if (m_rays[i]->IsCollision(physicalBody))
			{
				return true;
			}
		}
	}


	return false;
}

Bomb::State Bomb::GetState()
{
	return m_state;
}

void Bomb::SetPosition(int x, int y)
{
	x = m_positionInTilesCoordsX = x / TILE_SIZE;
	y = m_positionInTilesCoordsY = y / TILE_SIZE;

	SetPositionX(static_cast<float>(x)*TILE_SIZE + TILE_SIZE/2);
	SetPositionY(static_cast<float>(y)*TILE_SIZE + TILE_SIZE/2);

}

void Bomb::SetUpRay(TextureAtlas * atlas)
{
	m_rayTextureAtlas = atlas;
}

void Bomb::SetLevelPointer(Level * level)
{
	this->level = level;
}

void Bomb::Update(float dt)
{
	m_animator->Animate(dt);

	m_sprite.setPosition(GetPositionX(), GetPositionY());
	m_positionInTilesCoordsX = static_cast<int>(GetPositionX() / TILE_SIZE);
	m_positionInTilesCoordsY = static_cast<int>(GetPositionY() / TILE_SIZE);

	if (m_detonationClock.getElapsedTime() >= m_detonationTime && m_state < State::exploding)
	{
		FixPosition();
		level->DestroyTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY, false);
		m_state = State::exploding;
		explode();
	}
	else if (m_detonationClock.getElapsedTime() >= m_detonationTime + m_rayOnScreenTime && m_state < State::exploded)
	{
		m_state = State::exploded;

        for(unsigned int i=0;i < m_tilesToDeleteAfterExplosion.size();i++)
            level->DestroyTile(m_tilesToDeleteAfterExplosion[i].first, m_tilesToDeleteAfterExplosion[i].second);
	}


	if (m_state == State::exploding)
		for (unsigned int i = 0; i < m_rays.size(); i++)
			m_rays[i]->Update(dt);

}

Ray* Bomb::GetRayPhysicalBody(unsigned int side)
{
	return m_rays[side];
}

int Bomb::GetPositionInTileCoordinatesX()
{
	return m_positionInTilesCoordsX;
}

int * Bomb::GetPositionPointerInTileCoordinatesX()
{
	return &m_positionInTilesCoordsX;
}

int Bomb::GetPositionInTileCoordinatesY()
{
	return m_positionInTilesCoordsY;
}

int * Bomb::GetPositionPointerInTileCoordinatesY()
{
	return &m_positionInTilesCoordsY;
}

void Bomb::SetMoveDirection(sf::Vector2i direction)
{
	SetVelocity(SPEED * direction.x, SPEED*direction.y);
	m_direction = direction;
	m_isMoving = true;
}

void Bomb::StopMoving()
{
	m_isMoving = false;
}

bool Bomb::isMoving()
{
	return m_isMoving;
}

int Bomb::GetNextPositionInTileCoordsX()
{
	return m_positionInTilesCoordsX + m_direction.x;
}
int Bomb::GetNextPositionInTileCoordsY()
{
	return m_positionInTilesCoordsY + m_direction.y;
}

void Bomb::FixPosition()
{
	SetPositionX(m_positionInTilesCoordsX * TILE_SIZE + TILE_SIZE / 2);
	SetPositionY(m_positionInTilesCoordsY * TILE_SIZE + TILE_SIZE / 2);
}

void Bomb::SetVolume(float volume)
{
  m_explosionSound.setVolume(volume);
}

void Bomb::explode()
{
	m_explosionSound.play();
	for (unsigned int i = 0; i < m_rays.size(); i++)
	{
		m_rays[i] = new Ray(static_cast<Ray::Side>(i));
		m_rayAnimator = new Animator();
		m_rayAnimator->AddAnimationState("explosion",*m_rayTextureAtlas, 0, m_rayTextureAtlas->GetCount() - 1);
		m_rays[i]->SetAnimator(*m_rayAnimator);
		m_rays[i]->SetPosition(GetPositionX(), GetPositionY());
		m_rays[i]->SetRaySpriteSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
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
			if (level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY - i) <= TT::NONE_WITH_SHADOW)
				size=i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsY - size - 1 >= 0 && (level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY - size - 1) == TT::TileType::WEAK_WALL
			|| level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY - size - 1) == TT::TileType::DOUBLE_WEAK_WALL))
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX, m_positionInTilesCoordsY - ++size));

		break;
	case Ray::Down:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY + i) <= TT::NONE_WITH_SHADOW)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsY + size + 1 < level->GetHeight() && (level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY + size + 1) == TT::TileType::WEAK_WALL || level->GetTile(m_positionInTilesCoordsX, m_positionInTilesCoordsY + size + 1) == TT::TileType::DOUBLE_WEAK_WALL))
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX, m_positionInTilesCoordsY + ++size));
		break;
	case Ray::Left:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if ( level->GetTile(m_positionInTilesCoordsX - i, m_positionInTilesCoordsY) <= TT::NONE_WITH_SHADOW)
			{
				size = i;
			}
			else break;
		}

		if (size != MAX_RAY_SIZE && (level->GetTile(m_positionInTilesCoordsX - size - 1, m_positionInTilesCoordsY) == TT::TileType::WEAK_WALL || level->GetTile(m_positionInTilesCoordsX - size - 1, m_positionInTilesCoordsY) == TT::TileType::DOUBLE_WEAK_WALL))
		{
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX - ++size, m_positionInTilesCoordsY));
		}
		break;
	case Ray::Right:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetTile(m_positionInTilesCoordsX + i, m_positionInTilesCoordsY) <= TT::NONE_WITH_SHADOW)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && (level->GetTile(m_positionInTilesCoordsX + size + 1, m_positionInTilesCoordsY) == TT::TileType::WEAK_WALL || level->GetTile(m_positionInTilesCoordsX + size + 1, m_positionInTilesCoordsY) == TT::TileType::DOUBLE_WEAK_WALL))
			m_tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(m_positionInTilesCoordsX + ++size, m_positionInTilesCoordsY));

		break;
	default:
		break;
	}


	return size;
}

void Bomb::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(m_sprite);
	if (m_state == State::exploding)
	{
		for (unsigned int i = 0; i < m_rays.size(); ++i)
		{
			target.draw(*m_rays[i]);
		}
	}
}
