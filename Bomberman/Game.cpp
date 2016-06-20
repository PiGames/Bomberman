#include "Game.h"

Game::Game(size_t width, size_t height)
{
	m_window = new sf::RenderWindow();
	m_windowWidth = width;
	m_windowHeight = height;
	m_window->create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman | Created by PiGames", sf::Style::Close);
	m_window->setFramerateLimit(60);

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

	//SETTING UP LEVEL
	m_levelView->SetLevel(m_level, m_atlases[0]);
	m_level->SetLevelView(m_levelView);

	//-----------------------------

	/*SETTING UP PLAYERS - BEGIN*/
	for (int i = 0; i < m_numberOfPlayers; ++i)
	{
		m_playersAnimators[i]->AddAnimationState("default", *m_atlases[m_atlases.size() - m_numberOfPlayers + i], 0, m_atlases[m_atlases.size() - m_numberOfPlayers + i]->GetCount() - 1);
		m_playersAnimators[i]->SetLoop(true);

		m_players[i]->SetAnimator(*m_playersAnimators[i], m_atlases[m_atlases.size() - m_numberOfPlayers +i]->GetCellSizeX(), m_atlases[m_atlases.size() - m_numberOfPlayers + i]->GetCellSizeY());
		m_playersAnimators[i]->ChangeActiveState("default");

		m_players[i]->SetRespawns(3);
		//m_players[i]->SetUndamageableTime(sf::seconds(2)); //HACK Change this later 

		m_players[i]->SetUpBomb(m_atlases[1], m_atlases[2]);
		m_players[i]->SetLevelPointer(m_level);
		m_players[i]->SetPositionX((TILE_SIZE* m_level->GetWidth() - TILE_SIZE)*i + TILE_SIZE / 2);
		m_players[i]->SetPositionY((TILE_SIZE* m_level->GetHeight() - TILE_SIZE)*i + TILE_SIZE / 2);
		m_players[i]->SetColor(i);
	}
	/*SETTING UP PLAYERS - END*/

	//----------------------------

	m_physicsEngine->Init(m_level, &m_players);
	
	m_gui->Init(m_font, 30, m_windowWidth, m_windowHeight);
}


void Game::Run()
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

	std::map< std::pair<int, int>, Bomb*> bombs;

	for (unsigned int i = 0; i < m_players.size(); ++i)
	{
		m_players[i]->Update(deltaTime);
		if (m_players[i]->HasBomb())
		{
			bombs.emplace(std::pair<int, int>(m_players[i]->GetBomb()->GetPositionInTileCoordinatesX(), m_players[i]->GetBomb()->GetPositionInTileCoordinatesY()),
				m_players[i]->GetBomb());
		}
	}
	std::map<std::pair<int, int>, Bomb*>::iterator bomb;
	for (bomb = bombs.begin(); bomb != bombs.end(); ++bomb)
	{
		for (unsigned int i = 0; i < m_players.size(); ++i)
		{
			if (m_players[i]->IsCollidingWithBomb() && m_players[i]->GetBombCollidingWithCoordinates().x == bomb->first.first && m_players[i]->GetBombCollidingWithCoordinates().y == bomb->first.second)
			{
				bomb->second->SetMoveDirection(m_players[i]->GetSideBombCollidingWith());
				m_players[i]->SetIsCollidingWithBomb(false);
			}
		}

	
		for (unsigned int i = 0; i < m_players.size(); ++i)
		{
			if (bomb->second->isMoving())
			{
				std::cout << bomb->second->GetNextPositionInTileCoordsX() << " || " << bomb->second->GetNextPositionInTileCoordsY() << std::endl;
				if (static_cast<int>(m_players[i]->GetPositionX() / TILE_SIZE) == bomb->second->GetNextPositionInTileCoordsX()
					&& static_cast<int>(m_players[i]->GetPositionY() / TILE_SIZE) == bomb->second->GetNextPositionInTileCoordsY())
				{
					bomb->second->StopMoving();
				}
			}
		}
	}

	//TODO checking collisions after explosion

	m_gui->UpdateStats(&m_players);
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

	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_players[1]->OnActionKeyPressed();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
			m_players[0]->OnActionKeyPressed();

		// handle more events
	}
}
