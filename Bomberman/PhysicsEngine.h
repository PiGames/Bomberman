#pragma once
#include "Level.h"
#include "PhysicalBody.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <math.h>

class PhysicsEngine
{
public:
	const int tile_size = 64;

	PhysicsEngine();
	~PhysicsEngine();

	//Container contating all PhysicalBodys on Scene
	static std::vector<PhysicalBody*> PhysicalBodys_Pointer_Array;

	/// Sets current level data and reference to player
	/// <param name="level">level data</param>
	/// <param name="player">player's body</param>
	void Init(Level& level, PhysicalBody& player /* HACK 1st iteration only, add map later */);

	/// Check collisions, update speeds, ...
	/// <param name="dt">delta time in ms</param>
	void Update(const float& dt);

	static void Add_Physical_Body_into_Array(PhysicalBody* body_pointer);

private:
	Level* m_level;
	PhysicalBody* m_body;
	
	// add ref to bombs later
};

