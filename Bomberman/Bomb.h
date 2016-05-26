#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicalBody.h"
#include "Ray.h"
#include <vector>


class Bomb :public sf::Drawable, public PhysicalBody
{
private:
	void draw(sf::RenderWindow&, sf::RenderStates) const;

public:
	Bomb();
	~Bomb();

	///Check is anything colliding with rays
	/// <param name="floatRect"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool IsObjectInRay(sf::FloatRect & floatRect);
	///Sets texture of the bomb
	/// <param name="texture"> texture pointer (NOTE: MUST BE ALIVE)</param>
	void SetTexture(sf::Texture & texture);

protected:
	/// Puts bomb on position
	/// <param name="position"> position of bomb</param>
	void put(sf::Vector2f & position);

private:
	sf::Sprite m_sprite;
	sf::Texture * m_texture;
	struct rayLength
	{
		int up;
		int down;
		int left;
		int right;
	};
	std::vector<Ray> m_rays;
	sf::Time m_detonationTime;
	sf::Clock m_detonationClock;
};

