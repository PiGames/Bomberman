#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicalBody.h"


class Player : public sf::Drawable, public PhysicalBody
{
public:
	Player();
	~Player();


	/// Sets (simple) texture
	/// <param name="texture">simple (single) texture</param>
	void SetTexture(sf::Texture& texture /* HACK: 1st iteration only, change later to something else*/);
	
	/// Sets the player direction, possible values: -1, 0, 1
	/// <param name="x">direction x</param>
	/// <param name="y">direction y</param>
	void OnMoveKeyPressed(int x, int y);
	
	/// Sends the information about action key down (plant the bomb)
	void OnActionKeyPressed();

	/// Update player position, update states etc...
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite m_sprite;
};

