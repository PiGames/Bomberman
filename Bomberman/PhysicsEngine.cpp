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
	Add_Physical_Body_into_Array(&player);
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

	for (int i = 0; i < PhysicalBodys_Pointer_Array.size(); i++)
	{
		for (int y = 0; y < m_level->GetHeight(); ++y)
		{
			for (int x = 0; x < m_level->GetWidth(); ++x)
			{
				
				float distanse = sqrtf(powf(PhysicalBodys_Pointer_Array[i]->GetPositionX() - x*tile_size + tile_size / 2, 2) + powf(PhysicalBodys_Pointer_Array[i]->GetPositionY() - y*tile_size + tile_size / 2, 2));
				if (distanse < 120.f)
				{
					if (PhysicalBodys_Pointer_Array[i]->IsCollision(x*tile_size, y*tile_size, tile_size, tile_size))
					{	
						PhysicalBodys_Pointer_Array[i]->OnCollision(m_level->GetTile(x,y));
					
					}

				}
			}
		}

	}
}

std::vector <PhysicalBody*> PhysicsEngine::PhysicalBodys_Pointer_Array;
void PhysicsEngine::Add_Physical_Body_into_Array(PhysicalBody* body_pointer)
{
	PhysicalBodys_Pointer_Array.push_back(body_pointer);
}
