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
	/// Sets respawns count
	/// <param name="respawns"> respawns </param>
	void SetRespawns(short respawns);
	/// Adds value to current respawns
	/// <param name="val"> value to add to current respawns </param>
	void IncreaseRespawns(short val);
	/// Decrases value from current respawns
	void DecreaseRespawns(short val);
	/// Return Player's respawns
	/// <returns> Player's respawns </returns>
	short GetRespawnsCount();
	/// Sets the player direction, possible values: -1, 0, 1
	/// <param name="x">direction x</param>
	/// <param name="y">direction y</param>
	void OnMoveKeyPressed(int x, int y);

	bool HasBomb();

	Bomb* GetBomb();
	
	/// Sends the information about action key down (plant the bomb)
	void OnActionKeyPressed();
	void SetUpBomb(TextureAtlas* atlasBomb, TextureAtlas* atlasRay);
	
	void SetLevelPointer(Level * level);

	/// Update player position, update states etc...
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

	void OnBombCollision();

	bool isBombExplosion();

	void SetColor(int i);

	PhysicalBody GetRay(unsigned int side);

	bool GetIsAlive();
	void SetIsAlive(bool var);

	int GetPositionInTilesCoordsX();
	
	int GetPositionInTilesCoordsY();

	bool IsCollidingWithBomb();

	void SetIsCollidingWithBomb(bool value);

	sf::Vector2i GetSideBombCollidingWith();

	void SetSideBombCollidingWith(int x, int y);

	sf::Vector2i GetBombCollidingWithCoordinates();

	void ChangeTileToNone(int x, int y);

private:
	Level * level;
	sf::Sprite m_sprite;
	Animator* m_animator;

	Bomb * m_bomb;
	Animator* m_bombAnimator;
	TextureAtlas* m_bombTextureAtlas;

	TextureAtlas * m_bombRayTextureAtlas;
	short m_respawns;

	sf::Clock m_undamageableClock;
	sf::Time m_undamagabeTime;

	bool m_isAlive;

	bool m_isCollidingWithBomb;

	sf::Vector2i m_sideBombCollidingWith;

	sf::Vector2i m_bombCollidingWithLevelCoords;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void endGame();
};

