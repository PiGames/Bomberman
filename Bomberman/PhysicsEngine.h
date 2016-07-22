#pragma once
#include "Level.h"
#include "PhysicalBody.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Player.h"

class PhysicsEngine
{
public:
	const int TILE_SIZE = 64;

	PhysicsEngine();
	~PhysicsEngine();

	/// Sets current level data and reference to player
	/// <param name="level">level data</param>
	/// <param name="player">player's body</param>
	void Init(Level* level, std::vector<Player*>* players);

	/// Check collisions, update speeds, ...
	/// <param name="delta">delta time in ms</param>
	void Update(float delta);

private:
	///Logical level representation
	Level* m_level;

	///Physical level representation
	std::vector <std::vector<PhysicalBody*>> m_physicalLevel;


	///Physical player representation
	std::vector<Player*> m_players;

	void setBodyPositionInfo(int key);

	void setBodyPositionNextToAnotherBodyInAxisY(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);

	void setBodyPositionNextToAnotherBodyInAxisX(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);

};

