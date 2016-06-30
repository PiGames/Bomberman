#include "Menu.h"

void Menu::optHowTo()
{
}

void Menu::optCredits()
{
}

uint8_t Menu::update()
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		m_options[i]->Update(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);

		if (m_options[i]->IsClicked())
		{
			return i;
		}
	}

	return -1;
}

Menu::Menu()
{
	m_window.create(sf::VideoMode(m_SCREEN_WIDTH, m_SCREEN_HEIGHT), "Bomberman | Created by PiGames", sf::Style::Close);
	m_font = new sf::Font;

	if (!m_font->loadFromFile("data/Cat.ttf"))
	{
		std::cerr << "[!] Cannot load file: \"" << "data/Cat.ttf" << "\". Exiting...\n";
		std::cin.get();
		exit(1);
	}
	
	m_options[0] = new Option(m_font, "Play", 30, 300, 300, sf::Color::Blue , sf::Color::Black);
	m_options[1] = new Option(m_font, "How To Play", 30, 300, 380, sf::Color::Blue, sf::Color::Black);
	m_options[2] = new Option(m_font, "Credits", 30, 300, 460, sf::Color::Blue, sf::Color::Black);
	m_options[3] = new Option(m_font, "Exit", 30, 300, 540 , sf::Color::Blue, sf::Color::Black);

}

Menu::~Menu()
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		delete m_options[i];
	}
		delete m_font;
}

bool Menu::Run()
{
	sf::Event event;
	int8_t option;

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				exit(0);
			}
		}

		option = update();
		//im cleverst gui in the world hehe ~Con
		if (option != -1)
		{
			if (!option)
			{
				return true;
			}
			else if (option == 1)
			{
				optHowTo();
			}
			else if (option == 2)
			{
				optCredits();
			}
			else
			{
				return false;
			}

		}

		m_window.clear();
		m_window.draw(*m_options[0]);
		m_window.draw(*m_options[1]);
		m_window.draw(*m_options[2]);
		m_window.draw(*m_options[3]);
		m_window.display();

	}
}
