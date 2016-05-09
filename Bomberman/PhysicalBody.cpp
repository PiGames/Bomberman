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
	// TODO simple AABB collision check
	return false;
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
