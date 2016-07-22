#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animator.h"
#include "PhysicalBody.h"



class Ray :public PhysicalBody, public sf::Drawable
{
	const int TILE_SIZE = 64;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
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

	int GetSide();

	void SetRaySpriteSize(unsigned short size);

	void SetPosition(float x, float y);
	void Update(float dt);

private:
	/// True - horizontal, false - vertical
	bool m_orientation;
	sf::Sprite m_sprite;
	sf::Texture * m_texture;
	Side m_side;
	unsigned short m_size;
	Animator* m_animator;

};

