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

	/*BOMBS INFO GATHERING BEGIN */
	for (unsigned int i = 0; i < m_players->size(); ++i)
	{

		if ((*m_players)[i]->HasBomb())
		{
			bombs.emplace(std::pair<int*, int*>((*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesX(), (*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesY()),
				(*m_players)[i]->GetBomb());
		}
		if ((*m_players)[i]->isBombExplosion())
			for(unsigned int j =0 ; j<4 ; ++j)
				rays.push_back((*m_players)[i]->GetRay(j));
	}
	/*BOMBS INFO GATHERING END */


	for (bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
	{

		if (bomb->second->GetState() == Bomb::State::waitingForExplosion)
		{

			if (bomb->second->isMoving() &&
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

	for (unsigned int i = rays.size(); i > 0 ; --i)
	{

		for (unsigned int j = 0; j < m_players->size(); ++j)
		{
			if (rays[i-1]->IsCollision(*(*m_players)[j]))
				(*m_players)[j]->OnBombCollision();
		}
		rays.pop_back();
	}

	bombs.clear();
	
}
