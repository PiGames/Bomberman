#include "PhysicalBody.h"



PhysicalBody::PhysicalBody()
{
	m_sizeX = m_sizeY = m_posX = m_posY = m_vX = m_vY = 0.0f;

	
}


PhysicalBody::~PhysicalBody()
{
}


void PhysicalBody::SetVelocity(float x, float y)
{
	m_vX = x;
	m_vY = y;
}


void PhysicalBody::SetSize(float x, float y)
{
	m_sizeX = x;
	m_sizeY = y;
}


bool PhysicalBody::IsCollision(const float & x, const float & y, const float & sizeX, const float & sizeY)
{

	if (m_posX + m_sizeX < x || m_posX > x + sizeX) return false;
	if (m_posY + m_sizeY < y || m_posY > y + sizeY) return false;

	return true;
}


bool PhysicalBody::IsCollision(PhysicalBody & pyRef)
{
	return IsCollision(pyRef.GetPositionX(), pyRef.GetPositionY(), pyRef.GetSizeX(), pyRef.GetSizeY());
}


void PhysicalBody::Update(const float & dt)
{
	last_pos_x = m_posX;
	last_pos_y = m_posY;

	m_posX += m_vX * dt;
	m_posY += m_vY * dt;
}


float const PhysicalBody::GetPositionX()
{
	return m_posX;
}


float const PhysicalBody::GetPositionY()
{
	return m_posY;
}


float const PhysicalBody::GetSizeX()
{
	return m_sizeX;
}


float const PhysicalBody::GetSizeY()
{
	return m_sizeY;
}


float const PhysicalBody::GetVelocityX()
{
	return m_vX;
}


float const PhysicalBody::GetVelocityY()
{
	return m_vY;
}

void PhysicalBody::OnCollision(TT::TileType type)
{
	//std::cout << "Collision! " << "type: " << type << std::endl;
	//do something

	if (type == TT::INDESTRUCTIBLE_WALL)
	{
		SetLastPosition();
	}
}
void PhysicalBody::SetLastPosition()
{
	m_posX = last_pos_x;
	m_posY = last_pos_y;
}