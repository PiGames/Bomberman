#pragma once


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
	
	/// Updates state of the object, moves the object, called after collsion check
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

	
	float GetPositionX();
	float GetPositionY();
	
	float GetSizeX();
	float GetSizeY();
	
	float GetVelocityX();
	float GetVelocityY();

protected:
	float m_posX;
	float m_posY;

	float m_sizeX;
	float m_sizeY;

	float m_vX;
	float m_vY;
};

