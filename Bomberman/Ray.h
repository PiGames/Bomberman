#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animator.h"



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
	///Sets Animator
	void SetAnimator(Animator& animator);
	/// Check is anything coliding with ray
	/// <param name="floatRect"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool Colliding(sf::FloatRect & floatRect);
	///Sets texture of the bomb
	/// <param name="texture"> texture pointer (NOTE: MUST BE ALIVE)</param>

	int GetSide();

	void SetSize(unsigned short size);

	void SetPosition(float x, float y);
	void Update(const float &dt);
	sf::Drawable& GetSprite();
	sf::FloatRect GetCollider();

private:
	/// True - horizontal, false - vertical
	bool m_orientation;
	sf::Sprite m_sprite;
	sf::Texture * m_texture;
	Side m_side;
	unsigned short m_size;
	Animator* m_animator;
	
};

