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
	if(m_bomb==nullptr)// Je�li nie ma aktualnie �adnej bomby od gracza
	{
		m_bomb = new Bomb();
		m_bomb->SetBombTexture(*m_bombTexture);
		m_bomb->SetRayTexture(*m_bombRayTexture);
		m_bomb->SetDetonationTime(sf::seconds(2.5f));
		m_bomb->SetRayOnScreenTime(sf::seconds(1));
		m_bomb->SetPosition(GetPositionX(), GetPositionY());//pode�lij aktualn� pozycje gracza
		m_bomb->SetLevelPointer(*level);
	}
}

void Player::SetLevelPointer(Level & level)
{
	this->level = &level;
}

std::vector<sf::FloatRect> Player::GetBombRaysColliders()
{
	if (m_bomb != nullptr)
	{
		if (m_bomb->GetState() == Bomb::exploding)
		{
			return m_bomb->GetBombRaysColliders();
		}
	}
}

void Player::CheckIsPlayerInBombRay(std::vector<sf::FloatRect>* bombRays)
{
	//a moze zamiast colliderow bomby sama bombe i uzyc metory isobjectinray?
	if (m_bomb != nullptr)
	{
		if (m_bomb->IsObjectInRay(m_sprite.getGlobalBounds()))
		{
			reactWhenIsInBombRay();
			//return;
		}
		//moze else? Albo zrobic return tam na gorze? zeby gracz dostawal reakcje na bombe tylko raz?
		if (bombRays != nullptr)
		{
			for (int i = 0; i < bombRays->size(); i++)
			{
				//jak to w ogole dziala?????
				if (bombRays[i][i].intersects(m_sprite.getGlobalBounds()))
				{
					reactWhenIsInBombRay();
					//return;
				}
			}
		}
	}
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
		{//Je�li bomba wybuch�a to usu� jej obiekt i przestaw wska�nik na null
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

void Player::reactWhenIsInBombRay()
{
	//Animation etc
	std::cout << "Player is colliding with bomb ray\n";
}
