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

void Bomb::SetDetonationTime(sf::Time time)
{
	m_detonationTime = time;
}

void Bomb::SetRayOnScreenTime(sf::Time time)
{
	m_rayOnScreenTime = time;
}

bool Bomb::IsObjectInRay(sf::FloatRect floatRect)
{
	if (m_rays[0] != nullptr)
	{
		if (m_state == exploding)
		{
			if (m_sprite.getGlobalBounds().intersects(floatRect))
			{
				return true;
			}
		}

		for (int i = 0; i < m_rays.size(); i++)
		{
			if (m_rays[i]->Colliding(floatRect))
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
	x = m_positionInTilesCoordsX = x / TILE_SIZE; //konwersja pozycji na wspó³rzêdne kafli
	y = m_positionInTilesCoordsY = y / TILE_SIZE;

	SetPositionX(x*TILE_SIZE + TILE_SIZE/2);//ustaw na œrodku kafla na którym znajduje siê bomba
	SetPositionY(y*TILE_SIZE + TILE_SIZE/2);

}

void Bomb::SetLevelPointer(Level & level)
{
	this->level = &level;
}

void Bomb::Update()
{
	//aktualizacja pozycji, przyda siê przy ew. ruchu bomby
	m_sprite.setPosition(GetPositionX(), GetPositionY());
	m_positionInTilesCoordsX = GetPositionX() / TILE_SIZE; //konwersja pozycji na wspó³rzêdne kafli
	m_positionInTilesCoordsY = GetPositionY() / TILE_SIZE;

	//obs³uga stanów bomby
	if (m_detonationClock.getElapsedTime() >= m_detonationTime && m_state < State::exploding)
	{
		m_state = State::exploding;
		m_sprite.setTexture(*m_rayTexture);
		explode();
	}
	else if (m_detonationClock.getElapsedTime() >= m_detonationTime + m_rayOnScreenTime && m_state < State::exploded)
	{
		m_state = State::exploded;

		//usuñ kafle które by³y w zasiêgu bomby podczas eksplozji
        for(int i=0;i<m_tilesToDeleteAfterExplosion.size();i++)
            level->DestroyTile(m_tilesToDeleteAfterExplosion[i].first, m_tilesToDeleteAfterExplosion[i].second);
	}

}

std::vector<sf::FloatRect> Bomb::GetBombRaysColliders()
{
	std::vector<sf::FloatRect> vec;

	if (m_rays[0] != nullptr)
	{
		vec.push_back(m_sprite.getGlobalBounds());

		for (int i = 0; i < m_rays.size(); i++)
		{
			vec.push_back(m_rays[i]->GetCollider());
		}
	}

	return vec;
}

void Bomb::explode()
{

	for (int i = 0; i < m_rays.size(); i++)
	{
		m_rays[i] = new Ray(static_cast<Ray::Side>(i));

		m_rays[i]->SetTexture(*m_rayTexture);//zmieñ teksturê bomby na teksture promienia gdy nast¹pi wybuch
		m_rays[i]->SetPosition(GetPositionX(), GetPositionY());
		m_rays[i]->SetSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
	}
}

unsigned short Bomb::getRaySizeAfterCollisions(Ray::Side side)
{
	//kod wygl¹da na pojebany, ale w rzeczywisoœci jest bardzo prosty
	//Dla ka¿dego kejsa wykonuje sie bardzo podobny kod:
	//0. Ustaw domyœlny rozmiar na zero
	//1. SprawdŸ czy dalszy kafel od œrodka bomby jest pod³og¹(i czy mieœci siê w mapie)
	//1.1 Jeœli tak to zwiêksz rozmiar promienia i wróc do punktu nr 1.
	//1.2 Jeœli nie to przerwij pêtle i idŸ do kolejnego punktu (nr. 2)
	//2. SprawdŸ czy przypadkiem promieñ nie koliduje z kaflem który da siê rozwaliæ,
	//jeœli tak to zwiêksz rozmiar promienia(¿eby promieñ by³ na kaflu który rozwali)
	// oraz dodaj ten kafel do kontenere w którym przebywaj¹ce kafle zostan¹ rozwalone po wybuchu

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
			{
				size = i;
			}
			else break;
		}

		if (size != MAX_RAY_SIZE && m_positionInTilesCoordsX - size - 1 >= 0 && level->GetTile(m_positionInTilesCoordsX - size - 1, m_positionInTilesCoordsY) == TT::TileType::WEAK_WALL)
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

	target.draw(m_sprite);
	if (m_state == State::exploding)
	{
		for (int i = 0; i < m_rays.size(); ++i)
		{
			target.draw(m_rays[i]->GetSprite());
		}
	}
}
