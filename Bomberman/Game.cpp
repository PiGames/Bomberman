#include "Game.h"


Game::Game(size_t width, size_t height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Bomberman | Created by PiGames", sf::Style::Close);
}


Game::~Game()
{
}


void Game::Run()
{
	m_exit = false;
	sf::Clock clock;

	const std::string levelPath = "data/sample_level.txt";
	if (!m_level.LoadFromFile(levelPath))
	{
		std::cerr << "[!] Cannot load file: \"" << levelPath << "\". Exiting...\n";
		m_exit = true; // xd
		std::exit(1);
	}
	
	sf::Texture levelTextures; // HACK delete later, only for 1st iteration
	const std::string terrainPath = "data/sample_terraintextures.png";
	if (!levelTextures.loadFromFile(terrainPath))
	{
		std::cerr << "[!] Cannot load file: \"" << terrainPath << "\"Exiting...\n";
		m_exit = true;
		std::exit(2); // diff err codes: too fast console
	}
	m_levelView.SetLevel(&m_level, &levelTextures, 64 /* HACK: 1st iteration only, add atlas manager later */);
	
	
	sf::Texture playerTexture;
	const std::string playerTexturePath = "data/sample_playertexture.png";
	if (!playerTexture.loadFromFile(playerTexturePath))
	{
		std::cerr << "[!] Cannot load file: \"" << playerTexturePath << "\"Exiting...\n";
		m_exit = true;
		std::exit(3);
	}
	m_localPlayer.SetTexture(playerTexture);
	
	m_physicsEngine.Init(m_level, m_localPlayer.GetPhysicalBody());
	
	// main loop
	while (!m_exit)
	{
		processEvents();
	
		update(clock.getElapsedTime().asSeconds());
		clock.restart();

		draw();
	}
}


void Game::draw()
{
	m_window.clear();

	m_window.draw(m_levelView);
	// HACK bomb
	m_window.draw(m_localPlayer);


	m_window.display();
}


void Game::update(float deltaTime)
{
	m_physicsEngine.Update(deltaTime);
	m_localPlayer.Update(deltaTime);
}


void Game::processEvents()
{
	if (m_exit)
		return; // if exiting: skip event processing! 

	sf::Event event;
	
	int x = 0;
	int y = 0;

	// HACK 1st iteration only, add class Input later
	// handle horizontal axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		x = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		x = 1;
	
	// handle vertical axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		y = 1;

	m_localPlayer.OnMoveKeyPressed(x, y);

	
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}

		// handle more events
	}
}
