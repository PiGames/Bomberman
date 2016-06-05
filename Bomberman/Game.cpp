#include "Game.h"


Game::Game(size_t width, size_t height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_window.create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman | Created by PiGames", sf::Style::Close);
	m_window.setFramerateLimit(60);
}


Game::~Game()
{
}


void Game::Run()
{
	/* TMP INIT BEGIN*/
	const int RESOURCE_COUNT = 3;
	std::string resourcePaths[RESOURCE_COUNT] =
	{
		"data/sample_level.txt",
		"data/sample_terraintextures.png",
		"data/sample_playertextures.png"
	};
	if (!m_level.LoadFromFile(resourcePaths[0]))
	{
		std::cerr << "[!] Cannot load file: \"" << resourcePaths[0] << "\". Exiting...\n";
		std::exit(1);
	}
	
	// loading resources
	if (!m_atlasTerrain.LoadFromFile(resourcePaths[1]))
	{
		std::cerr << "[!] Cannot load resource: '" << resourcePaths[1] << std::endl;
		std::exit(1);
	}

	if (!m_atlasPlayer.LoadFromFile(resourcePaths[2]))
	{
		std::cerr << "[!] Cannot load resource: '" << resourcePaths[2] << std::endl;
		std::exit(1);
	}

	// setting up resources
	m_atlasTerrain.TrimByGrid(64, 64);
	m_atlasPlayer.TrimByGrid(32, 32);
	
	m_levelView.SetLevel(&m_level, &m_atlasTerrain);

	// setting up player
	Animator playerAnimator;
	playerAnimator.AddAnimationState("default", m_atlasPlayer, 0, m_atlasPlayer.GetCount() - 1);
	playerAnimator.SetLoop(true);

	m_localPlayer.SetAnimator(playerAnimator, m_atlasPlayer.GetCellSizeX(), m_atlasPlayer.GetCellSizeY());
	playerAnimator.ChangeActiveState("default");
	
	
	/* TMP INIT END*/
	m_physicsEngine.Init(m_level, m_localPlayer);

	m_exit = false;
	sf::Clock clock;
	
	// main loop
	while (!m_exit)
	{
		processEvents();
	
		float dt = clock.getElapsedTime().asSeconds();
		update(dt);
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
	m_localPlayer.CheckIsPlayerInBombRay(nullptr);
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
		//sf::Keyboard::Key actionKey = sf::Keyboard::Space; //Sets action key which is planting the bomb
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_localPlayer.TryPlantingTheBomb();

		// handle more events
	}
}
