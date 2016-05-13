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
	if (fabs(m_posX - x) < (m_sizeX + sizeX) && fabs(m_posY - y) < (m_sizeY + sizeY))
	{
		return true;
	}

	return false;
}

bool PhysicalBody::IsCollision(PhysicalBody & pyRef)
{
	return IsCollision(pyRef.GetPositionX(), pyRef.GetPositionY(), pyRef.GetSizeX(), pyRef.GetSizeY());
}


void PhysicalBody::Update(const float & dt)
{
	m_posX += m_vX * dt;
	m_posY += m_vY * dt;
}


float PhysicalBody::GetPositionX()
{
	return m_posX;
}


float PhysicalBody::GetPositionY()
{
	return m_posY;
}


float PhysicalBody::GetSizeX()
{
	return m_sizeX;
}


float PhysicalBody::GetSizeY()
{
	return m_sizeY;
}


float PhysicalBody::GetVelocityX()
{
	return m_vX;
}


float PhysicalBody::GetVelocityY()
{
	return m_vY;
}
