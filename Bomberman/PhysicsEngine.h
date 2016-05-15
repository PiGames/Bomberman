#pragma once
#include "Level.h"
#include "PhysicalBody.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <math.h>

class PhysicsEngine
{
public:
	const int TILE_SIZE = 64;

	PhysicsEngine();
	~PhysicsEngine();

	/// Sets current level data and reference to player
	/// <param name="level">level data</param>
	/// <param name="player">player's body</param>
	void Init(Level& level, PhysicalBody& player /* HACK 1st iteration only, add map later */);

	/// Check collisions, update speeds, ...
	/// <param name="delta">delta time in ms</param>
	void Update(const float& delta);

private:
	Level* m_level;
	PhysicalBody* m_body;
	
	enum BodyPositionState {OnSingleTile, OnTwoTilesHorizontal, OnTwoTilesVertical, OnFourTiles};

	int getBodyPositionState(PhysicalBody* body);

	void checkOnSingleTileCollision(PhysicalBody * body,int & x, int & y);
	void checkOnTwoTilesHorizontalCollision(PhysicalBody * body, int & x, int & y);
	void checkOnTwoTilesVerticalCollision(PhysicalBody * body, int & x, int & y);
};

