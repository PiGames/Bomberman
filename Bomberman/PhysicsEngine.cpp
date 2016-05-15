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
}


void PhysicsEngine::Update(const float & delta)
{
	BodyPositionState bodyState = BodyPositionState(getBodyPositionState(m_body));

	int x = m_body->GetPositionX / TILE_SIZE;
	int y = m_body->GetPositionY / TILE_SIZE;

	switch (bodyState)
	{
		case OnSingleTile:
			checkOnSingleTileCollision(m_body, x, y);
			break;
		case OnTwoTilesHorizontal:
			checkOnTwoTilesHorizontalCollision(m_body, x, y);
			break;
		case OnTwoTilesVertical:
			checkOnTwoTilesVerticalCollision(m_body, x, y);
	default:
		break;
	}
	
		
}

int PhysicsEngine::getBodyPositionState(PhysicalBody * body)
{
	int	upBound = (body->GetPositionY - body->GetSizeY / 2) / TILE_SIZE;
	int downBound = (body->GetPositionY + body->GetSizeY / 2) / TILE_SIZE;
	int leftBound = (body->GetPositionX - body->GetSizeX / 2) / TILE_SIZE;
	int rightBound = (body->GetPositionX + body->GetSizeX / 2) / TILE_SIZE;

	if (upBound == downBound && rightBound == leftBound)
		return OnSingleTile;

	else if (upBound != downBound && rightBound == leftBound)
		return OnTwoTilesVertical;

	else if (upBound == downBound && rightBound != leftBound)
		return OnTwoTilesHorizontal;

	return OnFourTiles;
}

void PhysicsEngine::checkOnSingleTileCollision(PhysicalBody * body, int & x, int & y)
{
	sf::IntRect* tileRect = new sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE);

	//TODO checkCollisions

}

void PhysicsEngine::checkOnTwoTilesHorizontalCollision(PhysicalBody * body, int & x, int & y)
{
}

void PhysicsEngine::checkOnTwoTilesVerticalCollision(PhysicalBody * body, int & x, int & y)
{
}
