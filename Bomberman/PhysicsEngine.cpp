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


void PhysicsEngine::Update(float delta)
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


		switch (m_players[i]->BodyInfo.state)
		{
		case PhysicalBody::OnSingleTile:
			if (m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY - 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][m_players[i]->BodyInfo.centerX]))
			{
				if (m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY - 1) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(0, -1);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][m_players[i]->BodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY + 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][m_players[i]->BodyInfo.centerX]))
			{
				if (m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY + 1) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(0, 1);
					m_players[i]->SetIsCollidingWithBomb(true);
				}

				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][m_players[i]->BodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX - 1, m_players[i]->BodyInfo.centerY) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX - 1]))
			{
				if (m_level->GetTile(m_players[i]->BodyInfo.centerX - 1, m_players[i]->BodyInfo.centerY) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(-1, 0);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX + 1, m_players[i]->BodyInfo.centerY) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX + 1]))
			{
				if (m_level->GetTile(m_players[i]->BodyInfo.centerX + 1, m_players[i]->BodyInfo.centerY) == TT::BOMB)
				{
					m_players[i]->SetSideBombCollidingWith(1, 0);
					m_players[i]->SetIsCollidingWithBomb(true);
				}
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case PhysicalBody::OnTwoTilesHorizontal:

			int additionTileXCoord;
			if (m_players[i]->BodyInfo.leftBound == m_players[i]->BodyInfo.centerX)
				additionTileXCoord = m_players[i]->BodyInfo.rightBound;
			else
				additionTileXCoord = m_players[i]->BodyInfo.leftBound;

			if (moveInYAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY - 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][m_players[i]->BodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][m_players[i]->BodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis  && m_level->GetTile(m_players[i]->BodyInfo.centerX, m_players[i]->BodyInfo.centerY + 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][m_players[i]->BodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][m_players[i]->BodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInYAxis &&m_level->GetTile(additionTileXCoord, m_players[i]->BodyInfo.centerY - 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if ( moveInYAxis &&m_level->GetTile(additionTileXCoord, m_players[i]->BodyInfo.centerY + 1) > TT::NONE_WITH_SHADOW && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case PhysicalBody::OnTwoTilesVertical:

			int additionTileYCoord;
			if (m_players[i]->BodyInfo.upBound == m_players[i]->BodyInfo.centerY)
				additionTileYCoord = m_players[i]->BodyInfo.downBound;
			else
				additionTileYCoord = m_players[i]->BodyInfo.upBound;

			if (moveInXAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX - 1, m_players[i]->BodyInfo.centerY) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis  && m_level->GetTile(m_players[i]->BodyInfo.centerX + 1, m_players[i]->BodyInfo.centerY) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[m_players[i]->BodyInfo.centerY][m_players[i]->BodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			if (moveInXAxis && m_level->GetTile(m_players[i]->BodyInfo.centerX - 1, additionTileYCoord) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_players[i]->BodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[additionTileYCoord][m_players[i]->BodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis &&m_level->GetTile(m_players[i]->BodyInfo.centerX + 1, additionTileYCoord) > TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_players[i]->BodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[additionTileYCoord][m_players[i]->BodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			break;

		case PhysicalBody::OnFourTiles:
			if(m_level->GetTile(m_players[i]->BodyInfo.leftBound, m_players[i]->BodyInfo.upBound) != TT::BOMB &&m_level->GetTile(m_players[i]->BodyInfo.leftBound, m_players[i]->BodyInfo.upBound )> TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_players[i]->BodyInfo.upBound][m_players[i]->BodyInfo.leftBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.upBound  ][m_players[i]->BodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.upBound ][m_players[i]->BodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_players[i]->BodyInfo.rightBound, m_players[i]->BodyInfo.upBound) != TT::BOMB &&m_level->GetTile(m_players[i]->BodyInfo.rightBound, m_players[i]->BodyInfo.upBound )> TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_players[i]->BodyInfo.upBound][m_players[i]->BodyInfo.rightBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.upBound  ][m_players[i]->BodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.upBound ][m_players[i]->BodyInfo.rightBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_players[i]->BodyInfo.leftBound, m_players[i]->BodyInfo.downBound) != TT::BOMB && m_level->GetTile(m_players[i]->BodyInfo.leftBound, m_players[i]->BodyInfo.downBound )> TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_players[i]->BodyInfo.downBound][m_players[i]->BodyInfo.leftBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.downBound  ][m_players[i]->BodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.downBound ][m_players[i]->BodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if(m_level->GetTile(m_players[i]->BodyInfo.rightBound, m_players[i]->BodyInfo.downBound) != TT::BOMB && m_level->GetTile(m_players[i]->BodyInfo.rightBound, m_players[i]->BodyInfo.downBound )> TT::NONE_WITH_SHADOW && bodyAfterXMovement.IsCollision(*m_physicalLevel[ m_players[i]->BodyInfo.downBound][m_players[i]->BodyInfo.rightBound ]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.downBound  ][m_players[i]->BodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(m_players[i], m_physicalLevel[ m_players[i]->BodyInfo.downBound ][m_players[i]->BodyInfo.rightBound]);
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
	m_players[key]->BodyInfo.centerX = static_cast<int>(m_players[key]->GetPositionX()) / TILE_SIZE;
	m_players[key]->BodyInfo.centerY = static_cast<int>(m_players[key]->GetPositionY()) / TILE_SIZE;

	m_players[key]->BodyInfo.upBound = static_cast<int>(m_players[key]->GetPositionY() - m_players[key]->GetSizeY() / 2) / TILE_SIZE;
	m_players[key]->BodyInfo.downBound = static_cast<int>(m_players[key]->GetPositionY() + m_players[key]->GetSizeY() / 2) / TILE_SIZE;
	m_players[key]->BodyInfo.leftBound = static_cast<int>(m_players[key]->GetPositionX() - m_players[key]->GetSizeX() / 2) / TILE_SIZE;
	m_players[key]->BodyInfo.rightBound = static_cast<int>(m_players[key]->GetPositionX() + m_players[key]->GetSizeX() / 2) / TILE_SIZE;

	if (m_players[key]->BodyInfo.upBound == m_players[key]->BodyInfo.downBound &&m_players[key]->BodyInfo.rightBound == m_players[key]->BodyInfo.leftBound)
		m_players[key]->BodyInfo.state = PhysicalBody::OnSingleTile;
	else if (m_players[key]->BodyInfo.upBound != m_players[key]->BodyInfo.downBound && m_players[key]->BodyInfo.rightBound == m_players[key]->BodyInfo.leftBound)
		m_players[key]->BodyInfo.state = PhysicalBody::OnTwoTilesVertical;
	else if (m_players[key]->BodyInfo.upBound == m_players[key]->BodyInfo.downBound && m_players[key]->BodyInfo.rightBound != m_players[key]->BodyInfo.leftBound)
		m_players[key]->BodyInfo.state = PhysicalBody::OnTwoTilesHorizontal;
	else
		m_players[key]->BodyInfo.state = PhysicalBody::OnFourTiles;

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

