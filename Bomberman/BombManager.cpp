#include "BombManager.h"
#include <iostream>


BombManager::BombManager()
{
}


BombManager::~BombManager()
{
}

void BombManager::Init(Level * level, std::vector<Player*>* players)
{
	m_level = level;
	m_players = players;
}

void BombManager::Update(const float & dt)
{
	for (unsigned int i = 0; i < m_players->size(); ++i)
	{

		if ((*m_players)[i]->HasBomb())
		{
			bombs.emplace(std::pair<int*, int*>((*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesX(), (*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesY()),
				(*m_players)[i]->GetBomb());
		}
	}
	
	for (bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
	{

		if (bomb->second->GetState() == Bomb::State::waitingForExplosion)
		{

			if (bomb->second->isMoving() && bomb->second->GetNextPositionInTileCoordsX() >= 0 && bomb->second->GetNextPositionInTileCoordsX() < m_level->GetWidth() &&
				bomb->second->GetNextPositionInTileCoordsY() >= 0 && bomb->second->GetNextPositionInTileCoordsY() < m_level->GetHeight() &&
				m_level->GetTile(bomb->second->GetNextPositionInTileCoordsX(), bomb->second->GetNextPositionInTileCoordsY()) == TT::NONE)
			{
				bomb->second->SetPositionX(bomb->second->GetPositionX() + bomb->second->GetVelocityX() * dt);
				bomb->second->SetPositionY(bomb->second->GetPositionY() + bomb->second->GetVelocityY() * dt);
				
				if (m_level->GetTile(bomb->second->GetPositionInTileCoordinatesX(), bomb->second->GetPositionInTileCoordinatesY()) == TT::BOMB)
					m_level->DestroyTile(bomb->second->GetPositionInTileCoordinatesX(), bomb->second->GetPositionInTileCoordinatesY(), false);
			}
			else
			{
				bomb->second->FixPosition();
				bomb->second->StopMoving();
				m_level->SetTileAsBomb(bomb->second->GetPositionInTileCoordinatesX(), bomb->second->GetPositionInTileCoordinatesY());
			}
		}

		for (unsigned int i = 0; i < m_players->size(); ++i)
		{
			if ((*m_players)[i]->IsCollidingWithBomb() && (*m_players)[i]->GetBombCollidingWithCoordinates().x == *(bomb->first.first) 
				&& (*m_players)[i]->GetBombCollidingWithCoordinates().y == *(bomb->first.second))
			{
				bomb->second->SetMoveDirection((*m_players)[i]->GetSideBombCollidingWith());
				(*m_players)[i]->SetIsCollidingWithBomb(false);
				(*m_players)[i]->SetSideBombCollidingWith(0,0);
 			}
		}


		for (unsigned int i = 0; i < m_players->size(); ++i)
		{
			if (bomb->second->isMoving())
			{
				if (((*m_players)[i])->GetPositionInTilesCoordsX() == bomb->second->GetNextPositionInTileCoordsX()
					&& ((*m_players)[i])->GetPositionInTilesCoordsY() == bomb->second->GetNextPositionInTileCoordsY())
				{
					bomb->second->StopMoving();
				}
			}
		}
	}
	bombs.clear();
}
