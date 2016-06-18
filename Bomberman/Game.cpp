#include "Game.h"


Game::Game(size_t width, size_t height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_window.create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman | Created by PiGames", sf::Style::Close);
	m_window.setFramerateLimit(60);

	//hmmm /Conrad
	Player p;
	m_players.push_back(p);
	m_players.push_back(p);
}


Game::~Game()
{
}


void Game::Run()
{
	// https://youtu.be/BzUWKSYjpgQ?t=1s
	// srlsy, make that init already
	/* TMP INIT BEGIN*/
	std::string resourcePaths[] =
	{
		"data/sample_level.txt",
		"data/sample_terraintextures.png",
		"data/sample_playertextures.png",
		"data/sample_bombtextures.png",
		"data/sample_raytextures.png",
		"data/sample_playertextures2.png"
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

	if (!m_atlasBomb.LoadFromFile(resourcePaths[3]))
	{
		std::cerr << "[!] Cannot load resource: '" << resourcePaths[3] << std::endl;
		std::exit(1);
	}
	if (!m_atlasBombRay.LoadFromFile(resourcePaths[4]))
	{
		std::cerr << "[!] Cannot load resource: '" << resourcePaths[4] << std::endl;
		std::exit(1);
	}
	if (!m_atlasPlayer2.LoadFromFile(resourcePaths[5]))
	{
		std::cerr << "[!] Cannot load resource: '" << resourcePaths[5] << std::endl;
		std::exit(1);
	}

	// setting up resources
	m_atlasTerrain.TrimByGrid(64, 64);
	m_atlasPlayer.TrimByGrid(32, 32);
	m_atlasPlayer2.TrimByGrid(32, 32);
	m_atlasBomb.TrimByGrid(64, 64);
	m_atlasBombRay.TrimByGrid(64, 64);

	m_levelView.SetLevel(&m_level, &m_atlasTerrain);
	m_level.SetLevelView(&m_levelView);


	// setting up player
	Animator playerAnimator;
	playerAnimator.AddAnimationState("default", m_atlasPlayer, 0, m_atlasPlayer.GetCount() - 1);
	playerAnimator.SetLoop(true);

	m_players[0].SetAnimator(playerAnimator, m_atlasPlayer.GetCellSizeX(), m_atlasPlayer.GetCellSizeY());
	playerAnimator.ChangeActiveState("default");

	m_players[0].SetRespawns(1);
	m_players[0].SetUndamageableTime(sf::seconds(2));

	// setting up player2
	Animator playerAnimator2;
	playerAnimator2.AddAnimationState("default", m_atlasPlayer2, 0, m_atlasPlayer2.GetCount() - 1);
	playerAnimator2.SetLoop(true);

	m_players[1].SetAnimator(playerAnimator2, m_atlasPlayer2.GetCellSizeX(), m_atlasPlayer2.GetCellSizeY());
	playerAnimator2.ChangeActiveState("default");

	m_players[1].SetRespawns(1);
	m_players[1].SetUndamageableTime(sf::seconds(2));

	
	// setting up bomb (and something for physic engine) 
	std::map<int, PhysicalBody*> players;
	for (unsigned i = 0; i < m_players.size(); ++i)
	{
		m_players[i].SetUpBomb(&m_atlasBomb, &m_atlasBombRay);
		m_players[i].SetLevelPointer(&m_level);//HACK only temporary, we'll figure something out to properly separate layer's (server and client)
		players.emplace(i, &m_players[i]);
	}
	
	m_physicsEngine.Init(m_level, &players);

	m_exit = false;
	sf::Clock clock;

	// setting up gui
	sf::Font font;
	if (!font.loadFromFile("data/Cat.ttf"))
	{
		exit(1);
	}
	m_gui = new GUI(font, 30, m_windowWidth, m_windowHeight);

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

	for (unsigned i = 0; i < m_players.size(); ++i)
	{
		m_window.draw(m_players[i]);
	}

	m_window.draw(*m_gui);

	m_window.display();
}


void Game::update(float deltaTime)
{
	m_physicsEngine.Update(deltaTime);

	std::vector<PhysicalBody> rays;

	for (unsigned int i = 0; i < m_players.size(); ++i)
	{
		m_players[i].Update(deltaTime);

		if (m_players[i].isBombExplosion())
			for (int j = 0; j < 4; ++j)
				rays.push_back(m_players[i].GetRay(j));	
	}

	for (unsigned int i = 0; i < m_players.size(); ++i)
		for (unsigned int j = 0; j < rays.size(); ++j)
			if (rays[j].IsCollision(m_players[i]))
			{
				std::cout << "[DEBUG] Player " << i << " is colliding with bomb ray\n";
				m_players[i].OnBombCollision();
			}

	m_gui->UpdateStats(m_players);
}


void Game::processEvents()
{
	if (m_exit)
	{
		return; // if exiting: skip event processing!
	}

	sf::Event event;
	std::pair<int,int> input[2];

	// HACK 1st iteration only, add class Input later
	// handle horizontal axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		input[0].first = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		input[0].first = 1;

	// handle vertical axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		input[0].second = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		 input[0].second = 1;
    
	// handle horizontal axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		input[1].first = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		input[1].first = 1;
   
	// handle vertical axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		input[1].second = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		input[1].second = 1;


	for (int i = 0; i < 2; ++i)
	{
		m_players[i].OnMoveKeyPressed(input[i].first, input[i].second);
	}

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_players[0].OnActionKeyPressed();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
			m_players[1].OnActionKeyPressed();

		// handle more events
	}
}
