#include "Player.h"



Player::Player()
	:m_bomb(nullptr)
{

}


Player::~Player()
{
}


void Player::SetAnimator(Animator& animator, size_t width, size_t height)
{
	float w = static_cast<float>(width);
	float h = static_cast<float>(height);

	float tileSize = 64; // HACK tmp only

	m_sprite.setOrigin(w / 2.f, h / 2.f);// TODO fix collision
	SetSize(w, h);
	
	m_animator = &animator;
	m_animator->SetSprite(m_sprite);

	SetPositionX(3 * tileSize + w); 
	SetPositionY(5 * tileSize + h);
	m_sprite.setPosition(sf::Vector2f(3 * tileSize + w, 5 * tileSize + h));
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
	if(m_bomb==nullptr)// Jeœli nie ma aktualnie ¿adnej bomby od gracza
	{
		m_bomb = new Bomb();
		m_bomb->SetBombTexture(*m_bombTexture);
		m_bomb->SetRayTexture(*m_bombRayTexture);
		m_bomb->SetDetonationTime(sf::seconds(2.5f));
		m_bomb->SetRayOnScreenTime(sf::seconds(1));
		m_bomb->SetPosition(GetPositionX(), GetPositionY());//podeœlij aktualn¹ pozycje gracza
		m_bomb->SetLevelPointer(*level);
	}
}

void Player::SetBombTexture(sf::Texture & texture)
{
	m_bombTexture = &texture;
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
	m_animator->Animate(dt);

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
		{//Jeœli bomba wybuch³a to usuñ jej obiekt i przestaw wskaŸnik na null
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
