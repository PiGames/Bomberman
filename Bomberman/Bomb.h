#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "PhysicalBody.h"
#include "Animator.h"
#include "Ray.h"
#include "Level.h"


class Bomb :public sf::Drawable, public PhysicalBody
{
public:
	static const int TILE_SIZE = 64;
	const int MAX_RAY_SIZE = 4;
	const int SPEED = 200;
	enum State
	{
		waitingForExplosion,
		exploding,
		exploded
	};

public:
	Bomb(bool setColor = false);
	~Bomb();
	///Sets Animator
	void SetAnimator(Animator& animator, size_t width, size_t height);
	///Sets time to detonation
	/// <param name="time"> time in seconds</param>
	void SetDetonationTime(sf::Time time);
	///Sets explosion time (time when explosion ray is on screen)
	/// <param name="time"> time in seconds</param>
	void SetRayOnScreenTime(sf::Time time);
	///Check is anything colliding with rays
	/// <param name="physicalBody"> collider of an object</param>
	/// <returns>true when is collision</returns>
	/// <returns>false when isn't collision</returns>
	bool IsObjectInRay(PhysicalBody & physicalBody);
	/// <returns>true when bomb exploded and rays are on</returns>
	/// <returns>false if not</returns>
	Bomb::State GetState();
	///Spawns bomb on position
	/// <param name="position"> position of bomb</param>
	void SetPosition(int x, int y);
	///Updates bomb status
	void SetUpRay(TextureAtlas* atlas);

	void SetLevelPointer(Level * level);

	void Update(float dt);

	Ray* GetRayPhysicalBody(unsigned int side);

	int GetPositionInTileCoordinatesX();
	int* GetPositionPointerInTileCoordinatesX();
	int GetPositionInTileCoordinatesY();
	int* GetPositionPointerInTileCoordinatesY();

	void SetMoveDirection(sf::Vector2i direction);

	void StopMoving();

	bool isMoving();

	int GetNextPositionInTileCoordsX();
	int GetNextPositionInTileCoordsY();

	void FixPosition();

	void SetVolume(float volume);

private:
	Animator* m_animator;
	Level* level;
	int m_positionInTilesCoordsX;
	int m_positionInTilesCoordsY;
	sf::Sprite m_sprite;
	struct rayLength
	{
		int up;
		int down;
		int left;
		int right;
	};
	std::vector<Ray*> m_rays;
	Animator* m_rayAnimator;
	TextureAtlas* m_rayTextureAtlas;
	sf::Time m_detonationTime;
	sf::Time m_rayOnScreenTime;
	sf::Clock m_detonationClock;
	std::vector<std::pair<int, int>>m_tilesToDeleteAfterExplosion;
	State m_state;
	sf::Vector2i m_direction;
	bool m_isMoving;
	void explode();

	unsigned short getRaySizeAfterCollisions(Ray::Side side);
	void draw(sf::RenderTarget&, sf::RenderStates) const;

	sf::Sound m_explosionSound;
	sf::SoundBuffer m_soundBuffer;
};
