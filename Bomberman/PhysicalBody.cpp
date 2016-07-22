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


bool PhysicalBody::IsCollision(float x, float y, float sizeX, float sizeY)
{
	return !(m_posY + m_sizeY / 2 < y - sizeY / 2) && !(m_posY - m_sizeY / 2 > y + sizeY / 2) &&
		!(m_posX + m_sizeX / 2 < x - sizeX / 2) && !( m_posX - m_sizeX / 2 > x + sizeX / 2);
}


bool PhysicalBody::IsCollision(PhysicalBody & pyRef)
{
	return IsCollision(pyRef.GetPositionX(), pyRef.GetPositionY(), pyRef.GetSizeX(), pyRef.GetSizeY());
}


float PhysicalBody::GetPositionX() const
{
	return m_posX;
}


float PhysicalBody::GetPositionY() const
{
	return m_posY;
}


float PhysicalBody::GetSizeX() const
{
	return m_sizeX;
}


float PhysicalBody::GetSizeY() const
{
	return m_sizeY;
}


float PhysicalBody::GetVelocityX() const
{
	return m_vX;
}


float PhysicalBody::GetVelocityY() const
{
	return m_vY;
}

void PhysicalBody::SetPositionX(float x)
{
	m_posX = x;
}

void PhysicalBody::SetPositionY(float y)
{
	m_posY = y;
}

void PhysicalBody::SetMovementX(float movement)
{
	movementX = movement;
}

void PhysicalBody::SetMovementY(float movement)
{
	movementY = movement;
}

