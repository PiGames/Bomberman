#pragma once
#include "Level.h"
#include "PhysicalBody.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>

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
	///Logical level representation
	Level* m_level;

	///Physical level representation
	std::vector <std::vector<PhysicalBody*>> m_physicalLevel; 
	
	enum BodyPositionState { OnSingleTile, OnTwoTilesHorizontal, OnTwoTilesVertical, OnFourTiles };

	struct MovableBodyInfo
	{
		BodyPositionState state;

		int	upBound; // casted to level index
		int downBound;
		int leftBound;
		int rightBound;
		int centerX;
		int centerY;
	};
	///Physical player representation
	PhysicalBody* m_body;

	MovableBodyInfo m_bodyInfo;


	void setBodyPositionInfo(PhysicalBody* body, MovableBodyInfo & bodyInfo);

	void setBodyPositionNextToAnotherBodyInYAxis(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);

	void setBodyPositionNextToAnotherBodyInXAxis(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);

	bool isInMapBoundsX(PhysicalBody & body);

	bool isInMapBoundsY(PhysicalBody & body);

	///The method decides itself which bounds set this body next to
	void setBodyPositionNextToXBound(PhysicalBody * body);

	///The method decides itself which bounds set this body next to
	void setBodyPositionNextToYBound(PhysicalBody * body);
};

