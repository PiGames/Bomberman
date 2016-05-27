#pragma once
#include <SFML\Graphics.hpp>
#include "PhysicalBody.h"
#include "Animator.h"

class Player : public sf::Drawable, public PhysicalBody
{
public:
	Player();
	~Player();


	/// Sets animator
	/// <param name="texture">animator</param>
	void SetAnimator(Animator& animator, size_t width, size_t height);
	
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
	Animator* m_animator;
};

