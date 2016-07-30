#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::options()
{
	volume = m_volumeSlider->GetValue() * 100.f;

	if (m_volumeSlider->GetValue() == 0)
	{
		m_volumeSlider->SetValue(0.6f);
		volume = 60;
	}
	else if (volume < 10.f)
	{
		volume = 0;
	}
	else if(volume > 87.f)
	{
		volume = 100;
	}
	m_music.setVolume(volume);
	optionsText[3].setString(std::to_string(static_cast<int>(volume)) + '%');

	playersLives = m_playersSlider->GetValue() * 5.f;
	if (m_playersSlider->GetValue() == 0)
	{
		m_playersSlider->SetValue(0.2f);
		playersLives = 2;
	}
	else if (playersLives < 0.6f)
	{
		playersLives = 0;
	}
	else if (playersLives >= 4.5f)
	{
		playersLives = 5;
	}
	playersLives = static_cast<int>(playersLives) + 1;
	optionsText[2].setString(std::to_string(static_cast<int>(playersLives)));
	
}

Menu::Menu(size_t width, size_t height)
{
	m_window = new sf::RenderWindow();
	m_windowWidth = width;
	m_windowHeight = height;
	m_window->create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman | Created by PiGames", sf::Style::Close);
	m_window->setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("data/icon.png");
	m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	m_buttonsPointers[0] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 2.3f - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "START");
	m_buttonsPointers[1] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "OPTIONS");
	m_buttonsPointers[2] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f + 100 - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "CREDITS");
	m_buttonsPointers[3] = new Button(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f + 200 - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "EXIT");

	m_playersSlider = new Slider(Slider::horizontal, sf::Vector2f(460, 180), 100, 30, 470, 80, 20, 10, sf::Color(0, 148, 154), sf::Color(229, 229, 229), sf::Color(160, 160, 160), sf::Color(255, 255, 255), false);
	m_volumeSlider = new Slider(Slider::horizontal, sf::Vector2f(460, 260), 100, 30, 470, 80, 20, 10, sf::Color(0, 148, 154), sf::Color(229, 229, 229), sf::Color(160, 160, 160), sf::Color(255, 255, 255), false);

	for (int i = 0; i < 4; ++i)
	{
		optionsText[i].setColor(sf::Color(0.f, 107, 139));
		optionsText[i].setCharacterSize(25);
		optionsText[i].setFont(m_font);
		optionsText[i].setStyle(sf::Text::Bold);
		
	}

	optionsText[0].setString("HP PER GAME:");
	optionsText[2].setString("3");
	optionsText[1].setString("VOLUME LEVEL:");
	optionsText[3].setString("60%");

	optionsText[0].setPosition(160, 180);
	optionsText[2].setPosition(400, 180);
	optionsText[1].setPosition(160, 260);
	optionsText[3].setPosition(385, 260);

	m_playersSlider->SetValue(0.4f);
	playersLives = 2;
	m_volumeSlider->SetValue(0.6f);
	volume = 60;

	m_backgroundTexture.loadFromFile("data/menuBackground.png");
	m_backgroundTexture.setSmooth(true);
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365));
	m_backgroundSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_backgroundTexture.getSize().x, (float)m_window->getSize().y / (float)m_backgroundTexture.getSize().y));

	m_pigamesLogoTexture.loadFromFile("data/menuPiGames.png");
	m_pigamesLogoTexture.setSmooth(true);
	m_pigamesLogoSprite.setTexture(m_pigamesLogoTexture);
	m_pigamesLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f, (float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f));

	m_gameLogoTexture.loadFromFile("data/menuLogo.png");
	m_gameLogoTexture.setSmooth(true);
	m_gameLogoSprite.setTexture(m_gameLogoTexture);
	m_gameLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f, (float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f));
	m_gameLogoSprite.setPosition(sf::Vector2f(m_window->getSize().x / 2.f - (m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x) / 2.f, m_window->getSize().y / 5.f - 30));

	m_font.loadFromFile("data/micross.ttf");
	m_gameVersion.setFont(m_font);
	m_gameVersion.setColor(sf::Color(32, 32, 32, 128));
	m_gameVersion.setString("Public 1.0.1");
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
	m_music.setVolume(volume);
	m_credits = false;

	if (!m_creditsTexture.loadFromFile("data/credits.png"))
	{
		std::cerr << "[!] Cannot load resource: 'data/credits.png'" << std::endl;
		std::cin.get();
		std::exit(1);
	}
	m_creditsSprite.setTexture(m_creditsTexture);

	m_options = false;

	m_optionReturnButton = new Button(sf::Vector2f(25, m_windowHeight - 100), sf::Vector2i(300, 75), "data/pressButton.png", "data/unpressButton.png", "RETURN TO MENU");
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

		if (m_options)
			options();

	}
}

void Menu::draw()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);

	if (m_credits)
	{
		m_window->draw(m_creditsSprite);
		m_window->display();
		return;
	}

	if (m_options)
	{
		m_window->draw(*m_optionReturnButton->GetSpritePointer());
		m_window->draw(*m_optionReturnButton->GetTextPointer());
		m_window->draw(*m_playersSlider);
		m_window->draw(*m_volumeSlider);
		for (int i = 0; i < 4; ++i)
		{
			m_window->draw(optionsText[i]);
		}
		m_window->display();
		return;
	}
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

	m_window->draw(*m_buttonsPointers[3]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[3]->GetTextPointer());

	m_window->display();
}

void Menu::processEvents()
{
	sf::Event event;
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		if (m_options)
		{
			m_playersSlider->Update(sf::Mouse::getPosition(*m_window), &event);
			m_volumeSlider->Update(sf::Mouse::getPosition(*m_window), &event);
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !m_credits)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), false);
				if (m_optionReturnButton->GetSpritePointer()->getGlobalBounds().contains(mouse))
					m_options = false;
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !m_credits)
		{
			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), false);
			
			if (m_buttonsPointers[0]->GetSpritePointer()->getGlobalBounds().contains(mouse))
			{
				m_music.stop();
				m_game = new Game(m_window);
				m_game->Initialize(volume, volume, playersLives);
				m_exit = !m_game->Run();
				m_music.play();
				delete m_game;
				return;
			}
			else
			{
				if (m_buttonsPointers[1]->GetSpritePointer()->getGlobalBounds().contains(mouse))
				{
					m_options = true;
				}
				if (m_buttonsPointers[2]->GetSpritePointer()->getGlobalBounds().contains(mouse))
					m_credits = true;

				if (m_buttonsPointers[3]->GetSpritePointer()->getGlobalBounds().contains(mouse))
					m_exit = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !m_credits)
		{
			if (m_options)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), true);
				break;
			}

			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), true);
		}

		if (m_credits)
			if (event.type == sf::Event::KeyPressed)
				m_credits = false;

		if (m_options)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_options = false;
	}
}
