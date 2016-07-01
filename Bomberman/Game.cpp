#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	m_window = window;

	/*ALLOCATING OBJECTS - BEGIN*/
	m_level = new Level();
	m_levelView = new LevelView();
	m_physicsEngine = new PhysicsEngine();
	
	m_numberOfPlayers = 2; //HACK Additional parameter should be passed to initialize this variable
	for (unsigned int i = 0; i < m_numberOfPlayers; ++i)
	{
		m_players.push_back(new Player());
		m_playersAnimators.push_back(new Animator());
	}

	for (unsigned int i = 0; i < 3 + m_numberOfPlayers; ++i)//HACK this code assume that there are 3 atlases beside players
	{
		m_atlases.push_back(new TextureAtlas());
	}

	m_bombManager = new BombManager();

	m_font = new sf::Font();

	m_gui = new GUI(); 

	/*ALLOCATING OBJECTS - END*/
}


Game::~Game()
{
	delete m_level;
	delete m_levelView;
	delete m_physicsEngine;
	for (unsigned int i = 0; i < m_numberOfPlayers; ++i)
	{
		delete m_players[i];
		delete m_playersAnimators[i];
	}

	for (unsigned int i = 0; i < 3 + m_numberOfPlayers; ++i)//HACK this code assume that there are 3 atlases beside players
	{
		delete m_atlases[i];
	}

	delete m_font;

	delete m_gui;
}

void Game::Initialize()
{
	int resourcePathsCount = 6;
	std::string resourcePaths[6] =
	{
		/*level file path */"data/sample_level.txt",
		/*GUI font path*/"data/Cat.ttf",
		/* terrain sprite sheet path*/"data/sample_terraintextures.png",
		/* bomb sprite sheet path*/"data/sample_bombtextures.png",
		/* bomb ray sprite sheet path*/"data/sample_raytextures.png",
		/* player sprite sheet path*/"data/sample_playertextures.png"
	};

	/* LOADING RESOURCES - BEGIN*/ 
	if (!m_level->LoadFromFile(resourcePaths[0]))
	{
		std::cerr << "[!] Cannot load file: \"" << resourcePaths[0] << "\". Exiting...\n";
		std::cin.get();
		std::exit(1);
	}

	if (!m_font->loadFromFile(resourcePaths[1]))
	{
		std::cerr << "[!] Cannot load file: \"" << resourcePaths[1] << "\". Exiting...\n";
		std::cin.get();
		exit(1);
	}

	for (unsigned int i = 0; i < m_atlases.size() - m_numberOfPlayers; ++i)
	{
		if (!m_atlases[i]->LoadFromFile(resourcePaths[i + 2/* becuase we do not include level path and font path*/]))
			{
				std::cerr << "[!] Cannot load resource: '" << resourcePaths[i + 2] << std::endl;
				std::cin.get();
				std::exit(1);
			}
	}
	for (unsigned int i = m_atlases.size() - m_numberOfPlayers; i < m_atlases.size(); ++i)
	{
		if (!m_atlases[i]->LoadFromFile(resourcePaths[resourcePathsCount - 1/*last resource - player texture*/]))
		{
			std::cerr << "[!] Cannot load resource: '" << resourcePaths[resourcePathsCount - 1] << std::endl;
			std::cin.get();
			std::exit(1);
		}
	}
	/* LOADING RESOURCES - END*/

	//----------------------------

	/*SETTING UP ANIMATORS - BEGIN*/
	for (unsigned int i = 0; i < m_atlases.size() - m_numberOfPlayers; ++i)
	{
		m_atlases[i]->TrimByGrid(TILE_SIZE, TILE_SIZE);
	}

	for (unsigned int i = m_atlases.size() - m_numberOfPlayers; i < m_atlases.size(); ++i)
	{
		m_atlases[i]->TrimByGrid(TILE_SIZE/2, TILE_SIZE/2);
	}
	/*SETTING UP ANIMATORS - END*/

	//-----------------------------

	initGameplay();

	/*SETTING UP PLAYERS - END*/

	//----------------------------

	m_bombManager->Init(m_level, &m_players);

	m_physicsEngine->Init(m_level, &m_players);
	
	m_gui->Init(m_font, 30, m_window->getSize().x, m_window->getSize().y);
}


bool Game::Run()
{
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
	return enterMenu;
}


void Game::draw()
{
	m_window->clear();

	m_window->draw(*m_levelView);

	for (unsigned i = 0; i < m_players.size(); ++i)
	{
		m_window->draw(*m_players[i]);
	}

	m_window->draw(*m_gui);

	m_window->display();
}


void Game::update(float deltaTime)
{
	m_physicsEngine->Update(deltaTime);

	for (short i = 0; i < m_players.size(); ++i)
	{
		if (!m_endOfGame)
		{
			m_players[i]->Update(deltaTime);
		}

		if (!m_players[i]->GetIsAlive())
		{
			m_endOfGame = true;

			if (!i)
			{
				m_players[1]->SetWin(true);
				break;
			}
			
			m_players[0]->SetWin(true);
			break;
		}
	}

	m_bombManager->Update(deltaTime);

	if (m_endOfGame && !m_exit)
	{
		m_gui->UpdateStats(&m_players, sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y, m_playAgain, m_exit, enterMenu);
	}
	else
	{
		m_gui->UpdateStats(&m_players, sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	}

	if (m_endOfGame && m_playAgain)
	{
		initGameplay();
	}
}


void Game::processEvents()
{
	if (m_exit)
	{
		return; // if exiting: skip event processing!
	}

	if (!m_endOfGame)
	{
		std::pair<int, int> input[2];

		// HACK 1st iteration only, add class Input later
		// handle horizontal axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			input[1].first = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			input[1].first = 1;

		// handle vertical axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			input[1].second = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			input[1].second = 1;

		// handle horizontal axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			input[0].first = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			input[0].first = 1;

		// handle vertical axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			input[0].second = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			input[0].second = 1;


		for (int i = 0; i < 2; ++i)
		{
			m_players[i]->OnMoveKeyPressed(input[i].first, input[i].second);
		}
	}	
	
	sf::Event event;

	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			enterMenu = false;
			break;
		}
		
		if (!m_endOfGame)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				m_players[1]->OnActionKeyPressed();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
				m_players[0]->OnActionKeyPressed();
		}
		
		// handle more events
	}
}

void Game::initGameplay()
{

	//SETTING UP LEVEL
	m_levelView->SetLevel(m_level, m_atlases[0]);
	m_level->SetLevelView(m_levelView);

	//-----------------------------

	/*SETTING UP PLAYERS - BEGIN*/
	for (int i = 0; i < m_numberOfPlayers; ++i)
	{
		m_playersAnimators[i]->AddAnimationState("default", *m_atlases[m_atlases.size() - m_numberOfPlayers + i], 0, m_atlases[m_atlases.size() - m_numberOfPlayers + i]->GetCount() - 1);
		m_playersAnimators[i]->SetLoop(true);

		m_players[i]->SetAnimator(*m_playersAnimators[i], m_atlases[m_atlases.size() - m_numberOfPlayers + i]->GetCellSizeX(), m_atlases[m_atlases.size() - m_numberOfPlayers + i]->GetCellSizeY());
		m_playersAnimators[i]->ChangeActiveState("default");

		m_players[i]->SetRespawns(3);
		m_players[i]->SetUpBomb(m_atlases[1], m_atlases[2]);
		m_players[i]->SetLevelPointer(m_level);

		if (!i)
			m_players[i]->SetRespawnPosition(1, 1);
		else
			m_players[i]->SetRespawnPosition(m_level->GetWidth() - 2, m_level->GetHeight() - 2);
		m_players[i]->SetAfterRespawnSafeTime(2.5f);
		m_players[i]->Spawn();

		m_players[i]->SetColor(i);
	}

	// For position change or something, just must be in init
	for (short i = 0; i < m_players.size(); ++i)
	{
		m_players[i]->Update(0);
		m_players[i]->SetWin(false);
		m_players[i]->SetRespawns(3);
		m_players[i]->SetAlive();
	}

	m_endOfGame = false;
	m_playAgain = false;
}
