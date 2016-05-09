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


void PhysicsEngine::Update(const float & dt)
{
	// TODO check collisions with terrain
	/*
		HINT: Najlepiej jest zasymulowac ruch i sprawdzic czy wtedy zaszla kolizja
		Mozliwe ze trzeba bedzie zreimplementowac pare rzeczy
		
		Najprostsza wersja zaklada cos takiego:
		if (m_body.IsCollision(tileX, tileY, tileSizeX, tileSizeY)
		{
			m_body.SetVelocity(0,0);
		}
		Jezeli kolizja w jakimkolwiek miejscu to zatrzymaj sie caly, najlepiej sprawdzac na ktorej osi kolizja i zatrzymywac tylko ruch w np pionie albo poziomie
	*/
}
