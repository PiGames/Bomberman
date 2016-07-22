#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	short GetRespawnsCount() const;
	/// Sets the player direction, possible values: -1, 0, 1
	/// <param name="x">direction x</param>
	/// <param name="y">direction y</param>
	void OnMoveKeyPressed(int x, int y);

	void SetAfterRespawnSafeTime(float value);

	bool HasBomb() const;

	Bomb* GetBomb() const;

	/// Sends the information about action key down (plant the bomb)
	void OnActionKeyPressed();
	void SetUpBomb(TextureAtlas* atlasBomb, TextureAtlas* atlasRay);

	void SetLevelPointer(Level * level);

	/// Update player position, update states etc...
	/// <param name="dt">delta time in seconds</param>
	void Update(float dt);

	bool IsTileCollidingInAxisX(size_t x) const;
	bool IsTileCollidingInAxisY(size_t y) const;

	void OnBombCollision();

	bool isBombExplosion() const;

	void SetColor(int i);

	Ray* GetRay(unsigned int side) const;

	bool GetIsAlive() const;
	void SetIsAlive(bool var);

	int GetPositionInTilesCoordsX() const;

	int GetPositionInTilesCoordsY() const;

	bool IsCollidingWithBomb() const;

	void SetIsCollidingWithBomb(bool value);

	sf::Vector2i GetSideBombCollidingWith() const;

	void SetSideBombCollidingWith(int x, int y);

	sf::Vector2i GetBombCollidingWithCoordinates() const;

	void SetWin(bool val);
	bool GetWin() const;

	void SetRespawnPosition(size_t x, size_t y);
	void Spawn();
	void Respawn();
	void SetAlive();
	void DeleteBomb();

	void SetVolume(float volume);

private:
	Level * level;
	sf::Sprite m_sprite;
	Animator* m_animator;

	Bomb * m_bomb;
	Animator* m_bombAnimator;
	TextureAtlas* m_bombTextureAtlas;

	TextureAtlas * m_bombRayTextureAtlas;
	short m_respawns;
	short m_maxNumberOfRespawns;
	bool m_canBeDamaged;
	sf::Clock m_respawnClock;
	sf::Time m_respawnSafeTime;

	bool m_isAlive;

	bool m_isCollidingWithBomb;

	sf::Vector2i m_respawnPosition;

	sf::Vector2i m_sideBombCollidingWith;

	sf::Vector2i m_bombCollidingWithLevelCoords;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void endGame();
	void managePlayersTextureDirection();

	bool m_win;

	sf::Sound m_soundHit;
	sf::Sound m_soundPlant;
	sf::SoundBuffer m_soundBufferHit;
	sf::SoundBuffer m_soundBufferPlant;
};
