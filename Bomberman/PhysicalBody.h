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
	
	float GetPositionX() const;
	float GetPositionY() const;
	
	float GetSizeX() const;
	float GetSizeY() const;
	
	float GetVelocityX() const;
	float GetVelocityY() const;

	/// Sets position of physical body representation 
	/// This method does not change visible position of a body!!!
	/// <param name ="x">X axis coordinate</param>
	
	void SetPositionX(float x);

	/// Sets position of physical body representation 
	/// This method does not change visible position of a body!!!
	/// <param name ="y">Y axis coordinate</param>
	void SetPositionY(float y);

	void SetMovementX(float movement);

	void SetMovementY(float movement);

protected:
	float m_posX;
	float m_posY;

	float m_sizeX;
	float m_sizeY;

	float m_vX;
	float m_vY;

	float movementX; //This is final value pre-checked for collisions occurance
	float movementY;
};

