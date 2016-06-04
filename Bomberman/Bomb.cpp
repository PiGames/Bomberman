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
	x = m_positionInTilesCoordsX = x / TILE_SIZE; //konwersja pozycji na wsp�rz�dne kafli
	y = m_positionInTilesCoordsY = y / TILE_SIZE;

	SetPositionX(x*TILE_SIZE + TILE_SIZE/2);//ustaw na �rodku kafla na kt�rym znajduje si� bomba
	SetPositionY(y*TILE_SIZE + TILE_SIZE/2);

}

void Bomb::SetLevelPointer(Level & level)
{
	this->level = &level;
}

void Bomb::Update()
{
	//aktualizacja pozycji, przyda si� przy ew. ruchu bomby
	m_sprite.setPosition(GetPositionX(), GetPositionY());
	m_positionInTilesCoordsX = GetPositionX() / TILE_SIZE; //konwersja pozycji na wsp�rz�dne kafli
	m_positionInTilesCoordsY = GetPositionY() / TILE_SIZE;

	//obs�uga stan�w bomby
	if (m_detonationClock.getElapsedTime() >= m_detonationTime && m_state < State::exploding)
	{
		m_state = State::exploding;
		m_sprite.setTexture(*m_rayTexture);
		explode();
	}
	else if (m_detonationClock.getElapsedTime() >= m_detonationTime + m_rayOnScreenTime && m_state < State::exploded)
	{
		m_state = State::exploded;

		//usu� kafle kt�re by�y w zasi�gu bomby podczas eksplozji
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

		m_rays[i]->SetTexture(*m_rayTexture);//zmie� tekstur� bomby na teksture promienia gdy nast�pi wybuch
		m_rays[i]->SetPosition(GetPositionX(), GetPositionY());
		m_rays[i]->SetSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
	}
}

unsigned short Bomb::getRaySizeAfterCollisions(Ray::Side side)
{
	//kod wygl�da na pojebany, ale w rzeczywiso�ci jest bardzo prosty
	//Dla ka�dego kejsa wykonuje sie bardzo podobny kod:
	//0. Ustaw domy�lny rozmiar na zero
	//1. Sprawd� czy dalszy kafel od �rodka bomby jest pod�og�(i czy mie�ci si� w mapie)
	//1.1 Je�li tak to zwi�ksz rozmiar promienia i wr�c do punktu nr 1.
	//1.2 Je�li nie to przerwij p�tle i id� do kolejnego punktu (nr. 2)
	//2. Sprawd� czy przypadkiem promie� nie koliduje z kaflem kt�ry da si� rozwali�,
	//je�li tak to zwi�ksz rozmiar promienia(�eby promie� by� na kaflu kt�ry rozwali)
	// oraz dodaj ten kafel do kontenere w kt�rym przebywaj�ce kafle zostan� rozwalone po wybuchu

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
