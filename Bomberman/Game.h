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
#include "GUI.h"


class Game
{
private:
	/// Draws all stuff on scene
	void draw();

	/// Updates state of all objects, called before draw()
	/// <param name="deltaTime">passed time from last draw frame in seconds</param>
	void update(float deltaTime);

	/// Process all events
	void processEvents();

public:
	Game(size_t width, size_t height);
	~Game();

	void Run();

private:
	size_t m_windowWidth;
	size_t m_windowHeight;
	std::vector<Player> m_players;
	bool m_exit;

	Level m_level;
	LevelView m_levelView;

	PhysicsEngine m_physicsEngine;

	TextureAtlas m_atlasTerrain;
	TextureAtlas m_atlasPlayer;
	TextureAtlas m_atlasPlayer2;
	TextureAtlas m_atlasBomb;
	TextureAtlas m_atlasBombRay;
	// probably we gonna dynamicly allocate memory for it (we don't need gameplay gui when we are in menu)
	GUI * m_gui;

	sf::RenderWindow m_window;

};

