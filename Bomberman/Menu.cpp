#include "Menu.h"


Menu::Menu(sf::RenderWindow* window)
{
	m_window = window;

	m_buttonsPointers[0] = new Button(sf::Vector2f(m_window->getSize().x/2-150, 300), sf::Vector2i(300, 75), "data/pressButton.png", "data/unpressButton.png", "START");

	
	m_backgroundTexture.loadFromFile("data/menuBackground.png");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	//m_backgroundSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365 ));
	m_backgroundSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_backgroundTexture.getSize().x, (float)m_window->getSize().y / (float)m_backgroundTexture.getSize().y));
	
	m_pigamesLogoTexture.loadFromFile("data/menuPiGames.png");
	m_pigamesLogoSprite.setTexture(m_pigamesLogoTexture);
	m_pigamesLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f, (float)m_window->getSize().y / (float)m_pigamesLogoTexture.getSize().y / 8.f));
}

Menu::~Menu()
{
}

void Menu::Run()
{
	 m_exit = false;

	while (!m_exit)
	{
		processEvents();
		draw();
	}
}

void Menu::draw()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);
	m_window->draw(m_pigamesLogoSprite);

	m_window->draw(*m_buttonsPointers[0]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[0]->GetTextPointer());

	

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
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), true);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), false);
			}
		}
	}




}
