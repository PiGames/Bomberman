#include "Menu.h"
#include <iostream>


Menu::Menu(size_t width, size_t height)
{
	m_window = new sf::RenderWindow();
	m_windowWidth = width;
	m_windowHeight = height;
	m_window->create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman | Created by PiGames", sf::Style::Close);
	m_window->setFramerateLimit(60);
	m_buttonsPointers[0] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y/2.3f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "START");
	m_buttonsPointers[1] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "CREDITS");
	m_buttonsPointers[2] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f + m_window->getSize().y / 1.7f - m_window->getSize().y / 2.3f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "EXIT");
	
	m_backgroundTexture.loadFromFile("data/menuBackground.png");
	m_backgroundTexture.setSmooth(true);
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365 ));
	m_backgroundSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_backgroundTexture.getSize().x, (float)m_window->getSize().y / (float)m_backgroundTexture.getSize().y));
	
	m_pigamesLogoTexture.loadFromFile("data/menuPiGames.png");
	m_pigamesLogoTexture.setSmooth(true);
	m_pigamesLogoSprite.setTexture(m_pigamesLogoTexture);
	m_pigamesLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f, (float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f));

	m_gameLogoTexture.loadFromFile("data/menuLogo.png");
	m_gameLogoTexture.setSmooth(true);
	m_gameLogoSprite.setTexture(m_gameLogoTexture);
	m_gameLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f, (float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f));
	m_gameLogoSprite.setPosition(sf::Vector2f(m_window->getSize().x / 2.f - (m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x) / 2.f, m_window->getSize().y/5.f));

	m_font.loadFromFile("data/micross.ttf");
	m_gameVersion.setFont(m_font);
	m_gameVersion.setColor(sf::Color(32, 32, 32, 128));
	m_gameVersion.setString("Alpha Verion 0.1a");
	m_gameVersion.setScale(0.6f, 0.6f);
	m_gameVersion.setPosition(m_gameLogoSprite.getPosition().x + m_gameLogoTexture.getSize().x - 50, m_gameLogoSprite.getPosition().y + m_pigamesLogoTexture.getSize().y);
	
	sf::FloatRect textRect = m_gameVersion.getLocalBounds();
	
	m_gameVersion.setPosition(m_gameLogoSprite.getPosition().x + m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x - textRect.width *0.8f, m_gameLogoSprite.getPosition().y + m_gameLogoTexture.getSize().y * m_gameLogoSprite.getScale().y);

	if (!m_music.openFromFile("data/menu.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'data/menu.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}

	m_music.play();
	m_music.setLoop(true);
}

Menu::~Menu()
{
}

void Menu::Run()
{
	 m_exit = false;

	while (!m_exit)
	{
		draw();
		processEvents();
	}
}

void Menu::draw()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);
	m_window->draw(m_pigamesLogoSprite);

	m_window->draw(m_gameLogoSprite);

	m_window->draw(m_gameVersion);

	m_window->draw(*m_buttonsPointers[0]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[0]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[1]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[1]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[2]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[2]->GetTextPointer());

	m_window->display();
}

void Menu::processEvents()
{
	sf::Event event;

	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), false);

			sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
			if (m_buttonsPointers[0]->GetSpritePointer()->getGlobalBounds().contains(mouse))
			{
				m_music.stop();
				m_game = new Game(m_window);
				m_game->Initialize();
				m_exit = !m_game->Run();
				m_music.play();
				delete m_game;
				return;
			}

			if (m_buttonsPointers[2]->GetSpritePointer()->getGlobalBounds().contains(mouse))
				m_exit = true;
			
		
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), true);
		}
	}
}
