#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "LevelView.h"
#include "Types.h"
#include "Player.h"
#include "PhysicsEngine.h"
#include "Animator.h"
#include "GUI.h"
#include "BombManager.h"


class Game
{
public: const int TILE_SIZE = 64;
private:
	/// Draws all stuff on scene
	void draw();

	/// Updates state of all objects, called before draw()
	/// <param name="deltaTime">passed time from last draw frame in seconds</param>
	void update(float deltaTime);

	/// Process all events
	void processEvents();
	/// Inits level and players (also after endGame)
	void initGameplay(const std::string & lvlPath);

void pause();

public:
	Game(sf::RenderWindow * window);
	~Game();
	void Initialize(float musicVolume, float soundVolume, int numberOfLives);
	bool Run();

private:
	unsigned m_windowWidth;
	unsigned m_windowHeight;

	bool enterMenu;
	bool m_exit;
	bool m_pause;
	
	Level* m_level;
	LevelView* m_levelView;
	int m_numberOfPlayers;
	std::vector<Player*> m_players;
	std::vector<Animator*>m_playersAnimators;
	PhysicsEngine* m_physicsEngine;
	std::vector<TextureAtlas*> m_atlases; // [0]-terrain, [1] - bomb,[3] - player , [>3] more players
	BombManager* m_bombManager;
	sf::Font* m_font;
	GUI * m_gui;

	sf::RenderWindow* m_window;

	bool m_endOfGame;
	bool m_playAgain;
	int numberOfRespawns;
	sf::Music m_music;
};
