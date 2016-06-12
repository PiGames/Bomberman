#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "LevelView.h"
#include "Types.h"
#include "Player.h"
#include "PhysicsEngine.h"
#include "Animator.h"

class Game
{
public:
	Game(size_t width, size_t height);
	~Game();

	void Run();


private:
	size_t m_windowWidth;
	size_t m_windowHeight;
	bool m_exit;
	sf::RenderWindow m_window;

	Level m_level;
	LevelView m_levelView;
	std::vector<Player> m_players;

	PhysicsEngine m_physicsEngine;

	TextureAtlas m_atlasTerrain;
	TextureAtlas m_atlasPlayer;
	TextureAtlas m_atlasPlayer2;
	TextureAtlas m_atlasBomb;
	TextureAtlas m_atlasBombRay;


	/// Draws all stuff on scene
	void draw();

	/// Updates state of all objects, called before draw()
	/// <param name="deltaTime">passed time from last draw frame in seconds</param>
	void update(float deltaTime);

	/// Process all events
	void processEvents();
};

