#include "PhysicsEngine.h"



PhysicsEngine::PhysicsEngine()
{
	
}


PhysicsEngine::~PhysicsEngine()
{
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

			m_physicalLevel[y][x]->SetPositionX(x*TILE_SIZE + TILE_SIZE/2);
			m_physicalLevel[y][x]->SetPositionY(y*TILE_SIZE + TILE_SIZE/2);
			m_physicalLevel[y][x]->SetSize(TILE_SIZE, TILE_SIZE);
		}
}


void PhysicsEngine::Update(const float & delta)
{
	//TODO check if player is not touching map bounds 

	setBodyPositionInfo(m_body, m_bodyInfo);

	float movementY = m_body->GetVelocityY()*delta;
	float movementX = m_body->GetVelocityX()*delta;

	PhysicalBody bodyAfterYMovement = *m_body;
	PhysicalBody bodyAfterXMovement = *m_body;

	bodyAfterYMovement.SetPositionY(m_body->GetPositionY() + movementY);
	bodyAfterXMovement.SetPositionX(m_body->GetPositionX() + movementX);

	bool moveInYAxis = true, moveInXAxis = true;

	switch (m_bodyInfo.state)
	{
		case OnSingleTile:
			if (m_bodyInfo.centerY >= 1 && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY - 1)!= TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]))
			{	
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (m_bodyInfo.centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (m_bodyInfo.centerX >= 1 && m_level->GetTile(m_bodyInfo.centerX - 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (m_bodyInfo.centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_bodyInfo.centerX + 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]))
			{	
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case OnTwoTilesHorizontal:
			
			int additionTileXCoord;
			if (m_bodyInfo.leftBound == m_bodyInfo.centerX)
				additionTileXCoord = m_bodyInfo.rightBound;
			else
				additionTileXCoord = m_bodyInfo.leftBound;

			if (m_bodyInfo.centerY >= 1 && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY -1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (m_bodyInfo.centerY + 1 < m_level->GetHeight() && m_level->GetTile(m_bodyInfo.centerX, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][m_bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (m_bodyInfo.centerY >= 1 && moveInYAxis &&m_level->GetTile(additionTileXCoord, m_bodyInfo.centerY - 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if (m_bodyInfo.centerY + 1 < m_level->GetHeight() && moveInXAxis &&m_level->GetTile(additionTileXCoord, m_bodyInfo.centerY + 1) != TT::NONE && bodyAfterYMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInYAxis(m_body, m_physicalLevel[m_bodyInfo.centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case OnTwoTilesVertical:
			
			int additionTileYCoord;
			if (m_bodyInfo.upBound == m_bodyInfo.centerY)
				additionTileYCoord = m_bodyInfo.downBound;
			else
				additionTileYCoord = m_bodyInfo.upBound;

			if (m_bodyInfo.centerX >= 1 && m_level->GetTile(m_bodyInfo.centerX - 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (m_bodyInfo.centerX + 1 < m_level->GetWidth() && m_level->GetTile(m_bodyInfo.centerX + 1, m_bodyInfo.centerY) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[m_bodyInfo.centerY][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			if (m_bodyInfo.centerX >= 1 && moveInXAxis && m_level->GetTile(m_bodyInfo.centerX - 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (m_bodyInfo.centerX + 1 < m_level->GetWidth() && moveInXAxis &&m_level->GetTile(m_bodyInfo.centerX + 1, additionTileYCoord) != TT::NONE && bodyAfterXMovement.IsCollision(*m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInXAxis(m_body, m_physicalLevel[additionTileYCoord][m_bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			break;
	default:
		break;
	}
	m_body->SetMovementX(0);
	m_body->SetMovementY(0);
	if (moveInXAxis)
		m_body->SetMovementX(movementX);
	if (moveInYAxis)
		m_body->SetMovementY(movementY);	
}

void PhysicsEngine::setBodyPositionInfo(PhysicalBody * body, MovableBodyInfo & bodyInfo)
{
	m_bodyInfo.centerX = m_body->GetPositionX() / TILE_SIZE;
	m_bodyInfo.centerY = m_body->GetPositionY() / TILE_SIZE;

	bodyInfo.upBound = (body->GetPositionY() - body->GetSizeY() / 2) / TILE_SIZE;
	bodyInfo.downBound = (body->GetPositionY() + body->GetSizeY() / 2) / TILE_SIZE;
	bodyInfo.leftBound = (body->GetPositionX() - body->GetSizeX() / 2) / TILE_SIZE;
	bodyInfo.rightBound = (body->GetPositionX() + body->GetSizeX() / 2) / TILE_SIZE;

	if (bodyInfo.upBound == bodyInfo.downBound && bodyInfo.rightBound == bodyInfo.leftBound)
		bodyInfo.state = OnSingleTile;
	else if (bodyInfo.upBound != bodyInfo.downBound && bodyInfo.rightBound == bodyInfo.leftBound)
		bodyInfo.state = OnTwoTilesVertical;
	else if (bodyInfo.upBound == bodyInfo.downBound && bodyInfo.rightBound != bodyInfo.leftBound)
		bodyInfo.state = OnTwoTilesHorizontal;
	else
		bodyInfo.state = OnFourTiles;

	//std::cout << "uB: " << bodyInfo.upBound << "| dB: " << bodyInfo.downBound << "| lB: " << bodyInfo.leftBound << "| rB: " << bodyInfo.rightBound<<std::endl;
}

void PhysicsEngine::checkOnSingleTileCollision(PhysicalBody * body, int & x, int & y)
{

	//TODO checkCollisions

}

void PhysicsEngine::checkOnTwoTilesHorizontalCollision(PhysicalBody * body, int & x, int & y)
{
}

void PhysicsEngine::checkOnTwoTilesVerticalCollision(PhysicalBody * body, int & x, int & y)
{
}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInYAxis(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionY() > tile->GetPositionY())
		body->SetPositionY(tile->GetPositionY() + tile->GetSizeY() / 2 + body->GetSizeY() / 2 + 0.1f);
	else
		body->SetPositionY(tile->GetPositionY() - tile->GetSizeY() / 2 - body->GetSizeY() / 2 - 0.1f);

	//std::cout << "Set Next To in Y" << std::endl;
}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInXAxis(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionX() > tile->GetPositionX())
		body->SetPositionX(tile->GetPositionX() + tile->GetSizeX() / 2 + body->GetSizeX() / 2 + 0.1f);
	else
		body->SetPositionX(tile->GetPositionX() - tile->GetSizeX() / 2 - body->GetSizeX() / 2 - 0.1f);

	//std::cout << "Set Next To in X" << std::endl;
}
