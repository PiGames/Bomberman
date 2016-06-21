#include "BombManager.h"



BombManager::BombManager()
{
}


BombManager::~BombManager()
{
}

void BombManager::Init(std::vector<Player*>* players)
{
	m_players = players;
}

void BombManager::Update()
{
	for (unsigned int i = 0; i < m_players->size(); ++i)
	{
		
		if ((*m_players)[i]->HasBomb())
		{
			bombs.emplace(std::pair<int, int>((*m_players)[i]->GetBomb()->GetPositionInTileCoordinatesX(), (*m_players)[i]->GetBomb()->GetPositionInTileCoordinatesY()),
				(*m_players)[i]->GetBomb());
		}
	}
	std::map<std::pair<int, int>, Bomb*>::iterator bomb;
	for (bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
	{
		for (unsigned int i = 0; i < m_players->size(); ++i)
		{
			if ((*m_players)[i]->IsCollidingWithBomb() && (*m_players)[i]->GetBombCollidingWithCoordinates().x == bomb->first.first && (*m_players)[i]->GetBombCollidingWithCoordinates().y == bomb->first.second)
			{
				bomb->second->SetMoveDirection((*m_players)[i]->GetSideBombCollidingWith());
				(*m_players)[i]->SetIsCollidingWithBomb(false);
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
}
