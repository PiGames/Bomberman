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


void PhysicsEngine::Init(Level & level, std::map<int,Player*>* players)
{
	m_level = &level;
	m_players = players;

	std::map<int, Player*>::iterator m_body;
	for (m_body = m_players->begin(); m_body != m_players->end(); ++m_body)
	{
		std::cout << "Player: " << m_body->first << std::endl;
		m_playersInfo.emplace(m_body->first, MovableBodyInfo());
	}

	m_physicalLevel.resize(m_level->GetHeight());

	for (unsigned int i = 0; i < m_physicalLevel.size(); ++i)
		m_physicalLevel[i].resize(m_level->GetWidth());

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
	std::map<int, Player*>::iterator m_body;
	for (m_body = m_players->begin(); m_body != m_players->end(); ++m_body)
	{
		setBodyPositionInfo(m_body->first);

		m_body->second->SetMovementX(0);
		m_body->second->SetMovementY(0);

		float movementY = m_body->second->GetVelocityY()*delta;
		float movementX = m_body->second->GetVelocityX()*delta;

		if (movementX == 0 && movementY == 0)
			return;

		PhysicalBody bodyAfterYMovement = *m_body->second;
		PhysicalBody bodyAfterXMovement = *m_body->second;

		bodyAfterYMovement.SetPositionY(m_body->second->GetPositionY() + movementY);
		bodyAfterXMovement.SetPositionX(m_body->second->GetPositionX() + movementX);

		bool moveInYAxis = true, moveInXAxis = true;

		if (!isInMapBoundsX(bodyAfterXMovement))
		{
			setBodyPositionNextToBoundX(m_body->second);
			moveInXAxis = false;
		}
		if (!isInMapBoundsY(bodyAfterYMovement))
			moveInYAxis = false;

		switch (m_playersInfo[m_body->first].state)
		{
		case OnSingleTile:
			if (moveInYAxis && m_playersInfo[m_body->first].centerY >= 1 && m_level->GetTile(m_playersInfo[m_body->first].centerX, m_playersInfo[m_body->first].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][m_playersInfo[m_body->first].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][m_playersInfo[m_body->first].centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_playersInfo[m_body->first].centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_playersInfo[m_body->first].centerX, m_playersInfo[m_body->first].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][m_playersInfo[m_body->first].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][m_playersInfo[m_body->first].centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && m_playersInfo[m_body->first].centerX >= 1 && m_level->GetTile(m_playersInfo[m_body->first].centerX - 1, m_playersInfo[m_body->first].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_playersInfo[m_body->first].centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_playersInfo[m_body->first].centerX + 1, m_playersInfo[m_body->first].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case OnTwoTilesHorizontal:

			int additionTileXCoord;
			if (m_playersInfo[m_body->first].leftBound == m_playersInfo[m_body->first].centerX)
				additionTileXCoord = m_playersInfo[m_body->first].rightBound;
			else
				additionTileXCoord = m_playersInfo[m_body->first].leftBound;

			if (moveInYAxis && m_playersInfo[m_body->first].centerY >= 1 && m_level->GetTile(m_playersInfo[m_body->first].centerX, m_playersInfo[m_body->first].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][m_playersInfo[m_body->first].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][m_playersInfo[m_body->first].centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_playersInfo[m_body->first].centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_playersInfo[m_body->first].centerX, m_playersInfo[m_body->first].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][m_playersInfo[m_body->first].centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][m_playersInfo[m_body->first].centerX]);
				moveInYAxis = false;
			}

			if (m_playersInfo[m_body->first].centerY >= 1 && moveInYAxis &&m_level->GetTile(additionTileXCoord, m_playersInfo[m_body->first].centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if (m_playersInfo[m_body->first].centerY + 1 < m_level->GetHeight() && moveInYAxis &&m_level->GetTile(additionTileXCoord, m_playersInfo[m_body->first].centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case OnTwoTilesVertical:

			int additionTileYCoord;
			if (m_playersInfo[m_body->first].upBound == m_playersInfo[m_body->first].centerY)
				additionTileYCoord = m_playersInfo[m_body->first].downBound;
			else
				additionTileYCoord = m_playersInfo[m_body->first].upBound;

			if (moveInXAxis && m_playersInfo[m_body->first].centerX >= 1 && m_level->GetTile(m_playersInfo[m_body->first].centerX - 1, m_playersInfo[m_body->first].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_playersInfo[m_body->first].centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_playersInfo[m_body->first].centerX + 1, m_playersInfo[m_body->first].centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[m_playersInfo[m_body->first].centerY][m_playersInfo[m_body->first].centerX + 1]);
				moveInXAxis = false;
			}

			if (m_playersInfo[m_body->first].centerX >= 1 && moveInXAxis && m_level->GetTile(m_playersInfo[m_body->first].centerX - 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_playersInfo[m_body->first].centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[additionTileYCoord][m_playersInfo[m_body->first].centerX - 1]);
				moveInXAxis = false;
			}
			else if (m_playersInfo[m_body->first].centerX + 1 < m_level->GetWidth() && moveInXAxis &&m_level->GetTile(m_playersInfo[m_body->first].centerX + 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_playersInfo[m_body->first].centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body->second, m_physicalLevel[additionTileYCoord][m_playersInfo[m_body->first].centerX + 1]);
				moveInXAxis = false;
			}

			break;
		}
		if (moveInXAxis)
		{
			m_body->second->SetMovementX(movementX);
		}
		if (moveInYAxis)
		{
			m_body->second->SetMovementY(movementY);
		}
	}
}

void PhysicsEngine::setBodyPositionInfo(int key)
{
	m_playersInfo[key].centerX = static_cast<int>((*m_players)[key]->GetPositionX()) / TILE_SIZE;
	m_playersInfo[key].centerY = static_cast<int>((*m_players)[key]->GetPositionY()) / TILE_SIZE;

	m_playersInfo[key].upBound = static_cast<int>((*m_players)[key]->GetPositionY() - (*m_players)[key]->GetSizeY() / 2) / TILE_SIZE;
	m_playersInfo[key].downBound = static_cast<int>((*m_players)[key]->GetPositionY() + (*m_players)[key]->GetSizeY() / 2) / TILE_SIZE;
	m_playersInfo[key].leftBound = static_cast<int>((*m_players)[key]->GetPositionX() - (*m_players)[key]->GetSizeX() / 2) / TILE_SIZE;
	m_playersInfo[key].rightBound = static_cast<int>((*m_players)[key]->GetPositionX() + (*m_players)[key]->GetSizeX() / 2) / TILE_SIZE;

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

bool PhysicsEngine::isInMapBoundsX(PhysicalBody & body)
{
	return !(body.GetPositionX() - body.GetSizeX() / 2.f <= m_physicalLevel[0][0]->GetPositionX() - TILE_SIZE / 2.f) &&
		!(body.GetPositionX() + body.GetSizeX() / 2.f >= m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionX() + TILE_SIZE / 2.f);
}

bool PhysicsEngine::isInMapBoundsY(PhysicalBody & body)
{
	return !(body.GetPositionY() - body.GetSizeY() / 2.f <= m_physicalLevel[0][0]->GetPositionY() - TILE_SIZE / 2.f) &&
		!(body.GetPositionY() + body.GetSizeY() / 2.f >= m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionY() + TILE_SIZE / 2.f);
}

void PhysicsEngine::setBodyPositionNextToBoundX(PhysicalBody * body)
{
	if (fabs(body->GetPositionX() - m_physicalLevel[0][0]->GetPositionX()) >
		fabs(body->GetPositionX() - m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionX()))
		body->SetPositionX(m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionX() 
			+ m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetSizeX() /2.f - body->GetSizeX() / 2.f - 0.1f);
	else
		body->SetPositionX(m_physicalLevel[0][0]->GetPositionX() - m_physicalLevel[0][0]->GetSizeX() / 2.f + body->GetSizeX() / 2.f + 0.1f);
}

void PhysicsEngine::setBodyPositionNextToBoundY(PhysicalBody * body)
{
	if (fabs(body->GetPositionY() - m_physicalLevel[0][0]->GetPositionY()) >
		fabs(body->GetPositionY() - m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionY()))
		body->SetPositionY(m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetPositionY()
			+ m_physicalLevel[m_level->GetHeight() - 1][m_level->GetWidth() - 1]->GetSizeY() / 2.f - body->GetSizeY() / 2.f - 0.1f);
	else
		body->SetPositionY(m_physicalLevel[0][0]->GetPositionY() - m_physicalLevel[0][0]->GetSizeY() / 2.f + body->GetSizeY() / 2.f + 0.1f);
}

