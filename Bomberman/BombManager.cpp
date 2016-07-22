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

void BombManager::Update(float dt)
{
	gatherBombInformation();

	handleBombKicking(dt);

	checkBombsAfterExplosionsCollisions();
}

void BombManager::handleBombKicking(float dt)
{
	for (it = bombs.begin(); it != bombs.end(); ++it)
	{
		Bomb* tmpBomb = it->second;

		if (tmpBomb->GetState() == Bomb::State::waitingForExplosion)
		{

			if (tmpBomb->isMoving() &&
				(m_level->GetTile(tmpBomb->GetNextPositionInTileCoordsX(), tmpBomb->GetNextPositionInTileCoordsY()) == TT::NONE || m_level->GetTile(tmpBomb->GetNextPositionInTileCoordsX(), tmpBomb->GetNextPositionInTileCoordsY()) == TT::NONE_WITH_SHADOW))
			{
				tmpBomb->SetPositionX(tmpBomb->GetPositionX() + tmpBomb->GetVelocityX() * dt);
				tmpBomb->SetPositionY(tmpBomb->GetPositionY() + tmpBomb->GetVelocityY() * dt);

				if (m_level->GetTile(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY()) == TT::BOMB)
					m_level->DestroyTile(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY(), false);
			}
			else
			{
				tmpBomb->FixPosition();
				tmpBomb->StopMoving();
				m_level->SetTileAsBomb(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY());
			}
		}

		for (unsigned int i = 0; i < m_players->size(); ++i)
		{
			if ((*m_players)[i]->IsCollidingWithBomb() && (*m_players)[i]->GetBombCollidingWithCoordinates().x == *(it->first.first)
				&& (*m_players)[i]->GetBombCollidingWithCoordinates().y == *(it->first.second))
			{
				tmpBomb->SetMoveDirection((*m_players)[i]->GetSideBombCollidingWith());
				(*m_players)[i]->SetIsCollidingWithBomb(false);
				(*m_players)[i]->SetSideBombCollidingWith(0, 0);
			}
		}


		for (unsigned int i = 0; i < m_players->size(); ++i)
		{
			if (tmpBomb->isMoving())
			{
				if (((*m_players)[i])->IsTileCollidingInAxisX(tmpBomb->GetNextPositionInTileCoordsX())
					&& ((*m_players)[i])->IsTileCollidingInAxisY(tmpBomb->GetNextPositionInTileCoordsY()))
				{
					tmpBomb->StopMoving();
				}
			}
		}
	}
	bombs.clear();
}

void BombManager::checkBombsAfterExplosionsCollisions()
{
	for (unsigned int i = rays.size(); i > 0; --i)
	{

		for (unsigned int j = 0; j < m_players->size(); ++j)
		{
			if (rays[i - 1]->IsCollision(*(*m_players)[j]))
				(*m_players)[j]->OnBombCollision();
		}
		rays.pop_back();
	}
}

void BombManager::gatherBombInformation()
{
	for (unsigned int i = 0; i < m_players->size(); ++i)
	{

		if ((*m_players)[i]->HasBomb())
		{
			bombs.emplace(std::pair<int*, int*>((*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesX(), (*m_players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesY()),
				(*m_players)[i]->GetBomb());
		}
		if ((*m_players)[i]->isBombExplosion())
			for (unsigned int j = 0; j < 4; ++j)
				rays.push_back((*m_players)[i]->GetRay(j));
	}
}

