#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicalBody.h"
#include "Animator.h"
#include "Bomb.h"


class Player : public sf::Drawable, public PhysicalBody
{
public:
	const int TILE_SIZE = 64;

	Player();
	~Player();


	/// Sets animator
	/// <param name="animator">animator</param>
	void SetAnimator(Animator& animator, size_t width, size_t height);
	/// Sets health point
	/// <param name="hp"> health points </param>
	void SetHealth(short hp);
	/// Adds value to current hp
	/// <param name="val"> value to add to current hp </param>
	void AddToHealth(short val);
	/// Sets the player direction, possible values: -1, 0, 1
	/// <param name="x">direction x</param>
	/// <param name="y">direction y</param>
	void OnMoveKeyPressed(int x, int y);
	
	/// Sends the information about action key down (plant the bomb)
	void OnActionKeyPressed();
	void SetUpBomb(TextureAtlas* atlasBomb, TextureAtlas* atlasRay);
	
	void SetLevelPointer(Level * level);

//	std::vector<PhysicalBody> GetBombRaysColliders();

	/// Update player position, update states etc...
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

	void OnBombCollision();

	bool isBombExplosion();

	PhysicalBody GetRay(unsigned int side);

private:
	Level * level;
	sf::Sprite m_sprite;
	Animator* m_animator;

	Bomb * m_bomb;
	Animator* m_bombAnimator;
	TextureAtlas* m_bombTextureAtlas;

	TextureAtlas * m_bombRayTextureAtlas;
	short m_health;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

