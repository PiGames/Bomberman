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


void PhysicsEngine::Init(Level & level, PhysicalBody & player)
{
	m_level = &level;
	m_body = &player;

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
	setBodyPositionInfo(m_body, m_bodyInfo);

	m_body->SetMovementX(0);
	m_body->SetMovementY(0);

	float movementY = m_body->GetVelocityY()*delta;
	float movementX = m_body->GetVelocityX()*delta;

	if (movementX == 0 && movementY == 0)
		return;
	
	PhysicalBody bodyAfterYMovement = *m_body;
	PhysicalBody bodyAfterXMovement = *m_body;

	bodyAfterYMovement.SetPositionY(m_body->GetPositionY() + movementY);
	bodyAfterXMovement.SetPositionX(m_body->GetPositionX() + movementX);

	bool moveInYAxis = true, moveInXAxis = true;

	if (!isInMapBoundsX(bodyAfterXMovement))
	{
		setBodyPositionNextToBoundX(m_body);
		moveInXAxis = false;
	}
	if (!isInMapBoundsY(bodyAfterYMovement))
		moveInYAxis = false;

	switch (m_bodyInfo.state)
	{
		case OnSingleTile:
			if (moveInYAxis && m_bodyInfo.centerY >= 1 && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY - 1)!= TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]))
			{	
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_bodyInfo.centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && m_bodyInfo.centerX >= 1 && m_level->GetTile(m_bodyInfo.centerX - 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_bodyInfo.centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_bodyInfo.centerX + 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]))
			{	
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case OnTwoTilesHorizontal:
			
			int additionTileXCoord;
			if (m_bodyInfo.leftBound == m_bodyInfo.centerX)
				additionTileXCoord = m_bodyInfo.rightBound;
			else
				additionTileXCoord = m_bodyInfo.leftBound;

			if (moveInYAxis && m_bodyInfo.centerY >= 1 && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY -1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && m_bodyInfo.centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (m_bodyInfo.centerY >= 1 && moveInYAxis &&m_level->GetTile(additionTileXCoord, m_bodyInfo.centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if (m_bodyInfo.centerY + 1 < m_level->GetHeight() && moveInYAxis &&m_level->GetTile(additionTileXCoord, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case OnTwoTilesVertical:
			
			int additionTileYCoord;
			if (m_bodyInfo.upBound == m_bodyInfo.centerY)
				additionTileYCoord = m_bodyInfo.downBound;
			else
				additionTileYCoord = m_bodyInfo.upBound;

			if (moveInXAxis && m_bodyInfo.centerX >= 1 && m_level->GetTile(m_bodyInfo.centerX - 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && m_bodyInfo.centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_bodyInfo.centerX + 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			if (m_bodyInfo.centerX >= 1 && moveInXAxis && m_level->GetTile(m_bodyInfo.centerX - 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (m_bodyInfo.centerX + 1 < m_level->GetWidth() && moveInXAxis &&m_level->GetTile(m_bodyInfo.centerX + 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(m_body, m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			break;
	default:
		break;
	}
	if (moveInXAxis)
		m_body->SetMovementX(movementX);
	if (moveInYAxis)
		m_body->SetMovementY(movementY);	
}

void PhysicsEngine::setBodyPositionInfo(PhysicalBody * body, MovableBodyInfo & bodyInfo)
{
	m_bodyInfo.centerX = static_cast<int>(m_body->GetPositionX()) / TILE_SIZE;
	m_bodyInfo.centerY = static_cast<int>(m_body->GetPositionY()) / TILE_SIZE;

	bodyInfo.upBound = static_cast<int>(body->GetPositionY() - body->GetSizeY() / 2) / TILE_SIZE;
	bodyInfo.downBound = static_cast<int>(body->GetPositionY() + body->GetSizeY() / 2) / TILE_SIZE;
	bodyInfo.leftBound = static_cast<int>(body->GetPositionX() - body->GetSizeX() / 2) / TILE_SIZE;
	bodyInfo.rightBound = static_cast<int>(body->GetPositionX() + body->GetSizeX() / 2) / TILE_SIZE;

	if (bodyInfo.upBound == bodyInfo.downBound && bodyInfo.rightBound == bodyInfo.leftBound)
		bodyInfo.state = OnSingleTile;
	else if (bodyInfo.upBound != bodyInfo.downBound && bodyInfo.rightBound == bodyInfo.leftBound)
		bodyInfo.state = OnTwoTilesVertical;
	else if (bodyInfo.upBound == bodyInfo.downBound && bodyInfo.rightBound != bodyInfo.leftBound)
		bodyInfo.state = OnTwoTilesHorizontal;
	else
		bodyInfo.state = OnFourTiles;

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

