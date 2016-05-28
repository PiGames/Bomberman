#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "PhysicalBody.h"
#include "Ray.h"


class Bomb :public sf::Drawable, public PhysicalBody
{
	const int TILE_SIZE = 64;
public:
	enum State
	{
		waitingForExplosion,
		exploding,
		exploded
	};

private:
	void draw(sf::RenderTarget&, sf::RenderStates) const;

public:
	Bomb();
	~Bomb();

	///Sets time to detonation 
	/// <param name="time"> time in seconds</param>
	void SetDetonationTime(sf::Time & time);
	///Sets explosion time (time when explosion ray is on screen)
	/// <param name="time"> time in seconds</param>
	void SetRayOnScreenTime(sf::Time & time);
	///Check is anything colliding with rays
	/// <param name="floatRect"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool IsObjectInRay(sf::FloatRect & floatRect);
	/// <returns>true when bomb exploded and rays are on</returns>
	/// <returns>false if not</returns>
	Bomb::State WhatState();
	///Sets texture of the bomb
	/// <param name="texture"> texture pointer (NOTE: MUST BE ALIVE)</param>
	void SetBombTexture(sf::Texture & texture);
	///Sets texture of ray
	/// <param name="texture"> texture pointer </param>
	void SetRayTexture(sf::Texture & texture);
	///Spawns bomb on position
	/// <param name="position"> position of bomb</param>
	void SetPosition(int x, int y);
	///Updates bomb status
	void Update();

private:
	int m_positionInTilesCoordsX;
	int m_positionInTilesCoordsY;
	sf::Sprite m_sprite;
	sf::Texture * m_bombTexture;
	sf::Texture * m_rayTexture;
	struct rayLength
	{
		int up;
		int down;
		int left;
		int right;
	};
	std::vector<Ray*> m_rays;
	sf::Time m_detonationTime;
	sf::Time m_rayOnScreenTime;
	sf::Clock m_detonationClock;

	State m_state;

	void explode();
};

