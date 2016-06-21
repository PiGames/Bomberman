#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{

}


PhysicsEngine::~PhysicsEngine()
{
	for (unsigned int y = 0; y < m_physicalLevel.size(); ++y)
		for (unsigned int x = 0; x < m_physicalLevel[y].size(); ++x)
			delete m_physicalLevel[y][x];
}


void PhysicsEngine::Init(Level * level, std::vector<Player*>* players)
{
	m_level = level;

	m_players.resize(players->size());
	for (unsigned int i = 0; i < m_players.size(); ++i)
	{
		m_players[i] = (*players)[i];
	}
	
	for (unsigned int i=0; i<m_players.size(); ++i)
	{
		m_playersInfo.push_back(MovableBodyInfo());
	}

	m_physicalLevel.resize(m_level->GetHeight());

	for (unsigned int i = 0; i < m_physicalLevel.size(); ++i)
	{
		m_physicalLevel[i].resize(m_level->GetWidth());
	}

	for (unsigned int y = 0; y < m_physicalLevel.size(); ++y)
		for (unsigned int x = 0; x < m_physicalLevel[y].size(); ++x)
		{
			m_physicalLevel[y][x] = new PhysicalBody();

			m_physicalLevel[y][x]->SetPositionX(static_cast<float>(x)*TILE_SIZE + TILE_SIZE/2);
			m_physicalLevel[y][x]->SetPositionY(static_cast<float>(y)*TILE_SIZE + TILE_SIZE/2);
			m_physicalLevel[y][x]->SetSize(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE));
		}
}


void PhysicsEngine::Update(const float & delta)
{
	for (unsigned int i = 0; i<m_players.size(); ++i)
	{

		setBodyPositionInfo(i);

		m_players[i]->SetMovementX(0);
		m_players[i]->SetMovementY(0);

		float movementY = m_players[i]->GetVelocityY()*delta;
		float movementX = m_players[i]->GetVelocityX()*delta;

		if (movementX == 0 && movementY == 0)
			continue;

		PhysicalBody bodyAfterYMovement = *m_players[i];
		PhysicalBody bodyAfterXMovement = *m_players[i];

		bodyAfterYMovement.SetPositionY(m_players[i]->GetPositionY() + movementY);
		bodyAfterXMovement.SetPositionX(m_players[i]->GetPositionX() + movementX);

		bool moveInYAxis = true, moveInXAxis = true;

		
		switch (m_playersInfo[i].state)
		{
		case OnSingleTile:
			if (m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY - 1][m_playersInfo[i].centerX]))
			{
				if (m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY - 1) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(0, -1);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY - 1][m_playersInfo[i].centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY + 1][m_playersInfo[i].centerX]))
			{
				if (m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY + 1) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(0, 1);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
			
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY + 1][m_playersInfo[i].centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && m_level->GetTile(m_playersInfo[i].centerX - 1, m_playersInfo[i].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX - 1]))
			{
				if (m_level->GetTile(m_playersInfo[i].centerX - 1, m_playersInfo[i].centerY) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(-1, 0);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_level->GetTile(m_playersInfo[i].centerX + 1, m_playersInfo[i].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX + 1]))
			{
				if (m_level->GetTile(m_playersInfo[i].centerX + 1, m_playersInfo[i].centerY) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(1, 0);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case OnTwoTilesHorizontal:

			int additionTileXCoord;
			if (m_playersInfo[i].leftBound == m_playersInfo[i].centerX)
				additionTileXCoord = m_playersInfo[i].rightBound;
			else
				additionTileXCoord = m_playersInfo[i].leftBound;

			if (moveInYAxis && m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY - 1][m_playersInfo[i].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY - 1][m_playersInfo[i].centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis  && m_level->GetTile(m_playersInfo[i].centerX, m_playersInfo[i].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY + 1][m_playersInfo[i].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY + 1][m_playersInfo[i].centerX]);
				moveInYAxis = false;
			}

			if (moveInYAxis &&m_level->GetTile(additionTileXCoord, m_playersInfo[i].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if ( moveInYAxis &&m_level->GetTile(additionTileXCoord, m_playersInfo[i].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_playersInfo[i].centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case OnTwoTilesVertical:

			int additionTileYCoord;
			if (m_playersInfo[i].upBound == m_playersInfo[i].centerY)
				additionTileYCoord = m_playersInfo[i].downBound;
			else
				additionTileYCoord = m_playersInfo[i].upBound;

			if (moveInXAxis && m_level->GetTile(m_playersInfo[i].centerX - 1, m_playersInfo[i].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis  && m_level->GetTile(m_playersInfo[i].centerX + 1, m_playersInfo[i].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_playersInfo[i].centerY][m_playersInfo[i].centerX + 1]);
				moveInXAxis = false;
			}

			if (moveInXAxis && m_level->GetTile(m_playersInfo[i].centerX - 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_playersInfo[i].centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[additionTileYCoord][m_playersInfo[i].centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis &&m_level->GetTile(m_playersInfo[i].centerX + 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_playersInfo[i].centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[additionTileYCoord][m_playersInfo[i].centerX + 1]);
				moveInXAxis = false;
			}

			break;

		case OnFourTiles:
			if(m_level->GetTile(m_playersInfo[i].leftBound, m_playersInfo[i].upBound) != TT::BOMB &&m_level->GetTile(m_playersInfo[i].leftBound, m_playersInfo[i].upBound )!= TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_playersInfo[i].upBound][m_playersInfo[i].leftBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_playersInfo[i].upBound  ][m_playersInfo[i].leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_playersInfo[i].upBound ][m_playersInfo[i].leftBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_playersInfo[i].rightBound, m_playersInfo[i].upBound) != TT::BOMB &&m_level->GetTile(m_playersInfo[i].rightBound, m_playersInfo[i].upBound )!= TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_playersInfo[i].upBound][m_playersInfo[i].rightBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_playersInfo[i].upBound  ][m_playersInfo[i].rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_playersInfo[i].upBound ][m_playersInfo[i].rightBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_playersInfo[i].leftBound, m_playersInfo[i].downBound) != TT::BOMB && m_level->GetTile(m_playersInfo[i].leftBound, m_playersInfo[i].downBound )!= TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_playersInfo[i].downBound][m_playersInfo[i].leftBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_playersInfo[i].downBound  ][m_playersInfo[i].leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_playersInfo[i].downBound ][m_playersInfo[i].leftBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_playersInfo[i].rightBound, m_playersInfo[i].downBound) != TT::BOMB && m_level->GetTile(m_playersInfo[i].rightBound, m_playersInfo[i].downBound )!= TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_playersInfo[i].downBound][m_playersInfo[i].rightBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_playersInfo[i].downBound  ][m_playersInfo[i].rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_playersInfo[i].downBound ][m_playersInfo[i].rightBound]);
				moveInYAxis = false;
			}
		}
		if (moveInXAxis)
		{
			m_players[i]->SetMovementX(movementX);
		}
		if (moveInYAxis)
		{
			m_players[i]->SetMovementY(movementY);
		}
	}
}

void PhysicsEngine::setBodyPositionInfo(int key)
{
	m_playersInfo[key].centerX = static_cast<int>(m_players[key]->GetPositionX()) / TILE_SIZE;
	m_playersInfo[key].centerY = static_cast<int>(m_players[key]->GetPositionY()) / TILE_SIZE;

	m_playersInfo[key].upBound = static_cast<int>(m_players[key]->GetPositionY() - m_players[key]->GetSizeY() / 2) / TILE_SIZE;
	m_playersInfo[key].downBound = static_cast<int>(m_players[key]->GetPositionY() + m_players[key]->GetSizeY() / 2) / TILE_SIZE;
	m_playersInfo[key].leftBound = static_cast<int>(m_players[key]->GetPositionX() - m_players[key]->GetSizeX() / 2) / TILE_SIZE;
	m_playersInfo[key].rightBound = static_cast<int>(m_players[key]->GetPositionX() + m_players[key]->GetSizeX() / 2) / TILE_SIZE;

	if (m_playersInfo[key].upBound == m_playersInfo[key].downBound &&m_playersInfo[key].rightBound == m_playersInfo[key].leftBound)
		m_playersInfo[key].state = OnSingleTile;
	else if (m_playersInfo[key].upBound != m_playersInfo[key].downBound && m_playersInfo[key].rightBound == m_playersInfo[key].leftBound)
		m_playersInfo[key].state = OnTwoTilesVertical;
	else if (m_playersInfo[key].upBound == m_playersInfo[key].downBound && m_playersInfo[key].rightBound != m_playersInfo[key].leftBound)
		m_playersInfo[key].state = OnTwoTilesHorizontal;
	else
		m_playersInfo[key].state = OnFourTiles;

}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInAxisY(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionY() > tile->GetPositionY())
		body->SetPositionY(tile->GetPositionY() + tile->GetSizeY() / 2 + body->GetSizeY() / 2 + 0.1f);
	else
		body->SetPositionY(tile->GetPositionY() - tile->GetSizeY() / 2 - body->GetSizeY() / 2 - 0.1f);
}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInAxisX(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionX() > tile->GetPositionX())
		body->SetPositionX(tile->GetPositionX() + tile->GetSizeX() / 2 + body->GetSizeX() / 2 + 0.1f);
	else
		body->SetPositionX(tile->GetPositionX() - tile->GetSizeX() / 2 - body->GetSizeX() / 2 - 0.1f);
}

