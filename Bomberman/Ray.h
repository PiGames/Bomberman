#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Ray
{
	const int TILE_SIZE = 64;
public:
	enum Side
	{
		Up,
		Down,
		Left,
		Right
	};

	Ray(Side side);
	~Ray();
	/// Check is anything coliding with ray
	/// <param name="floatRect"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool Colliding(sf::FloatRect & floatRect);
	///Sets texture of the bomb
	/// <param name="texture"> texture pointer (NOTE: MUST BE ALIVE)</param>
	void SetTexture(sf::Texture * texture);

	int GetSide();

	void SetSize(unsigned short size);

	void SetPosition(float x, float y);

	sf::Drawable& GetSprite();
	sf::FloatRect GetCollider();

private:
	/// True - horizontal, false - vertical
	bool m_orientation;
	sf::Sprite m_sprite;
	sf::Texture * m_texture;
	std::vector<int> m_sections;
	Side m_side;
	unsigned short m_size;
	
};

