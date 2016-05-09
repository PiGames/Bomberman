#pragma once
#include "Level.h"
#include "PhysicalBody.h";

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	/// Sets current level data and reference to player
	/// <param name="level">level data</param>
	/// <param name="player">player's body</param>
	void Init(Level& level, PhysicalBody& player /* HACK 1st iteration only, add map later */);

	/// Check collisions, update speeds, ...
	/// <param name="dt">delta time in ms</param>
	void Update(const float& dt);

private:
	Level* m_level;
	PhysicalBody* m_body;
	// add ref to bombs later
};

