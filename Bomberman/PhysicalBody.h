#pragma once
#include <math.h>
#include "Types.h"
#include <iostream>
class PhysicalBody
{
public:
	PhysicalBody();
	~PhysicalBody();


	/// Sets the velocity
	/// <param name="x">x velocity</param>
	/// <param name="y">y velocity</param>
	void SetVelocity(float x, float y);

	/// Sets the object size
	/// <param name="x">width</param>
	/// <param name="y">height</param>
	void SetSize(float x, float y);
	
	/// Check collision between objects
	/// <param name="x">x position</param>
	/// <param name="y">y position</param>
	/// <param name="sizeX">width</param>
	/// <param name="sizeY">height</param>
	bool IsCollision(const float& x, const float& y, const float& sizeX, const float& sizeY);
	/// Check collision between objects
	/// <param name="pyRef">PhysicalBody reference</param>
	bool IsCollision(PhysicalBody& pyRef);

	/// Updates state of the object, moves the object, called after collsion check
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

	void OnCollision(TT::TileType type);
	
	float const GetPositionX();
	float const GetPositionY();
	
	float const GetSizeX();
	float const GetSizeY();
	
	float const GetVelocityX();
	float const GetVelocityY();

	
	//It is temporary!!
	void SetLastPosition();

protected:
	float m_posX;
	float m_posY;

	float m_sizeX;
	float m_sizeY;

	float m_vX;
	float m_vY;

	//It is temporary!!
	float last_pos_x;
	float last_pos_y;

};

