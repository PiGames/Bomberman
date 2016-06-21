#include "GUI.h"


void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::vector<sf::Text> texts;


	for (short i = 0; i < m_respawns.size(); ++i)
	{
		sf::Text tempText;
		tempText.setFont(*m_font);
		tempText.setCharacterSize(m_textSize);
		tempText.setPosition(0, 0);
		tempText.setString("Player " + std::to_string(i+1) + std::string(" respawns:") + std::to_string(m_respawns[i]));

		if (i == 1)
		{
			tempText.setPosition(tempText.getPosition().x + m_screenWidth - tempText.getGlobalBounds().width-10, tempText.getPosition().y);
			tempText.setColor(sf::Color::Green);
		}
		else 
		{
			tempText.setPosition(tempText.getPosition().x +10, tempText.getPosition().y);
			tempText.setColor(sf::Color::Blue);
		}
		

		texts.push_back(tempText);
		target.draw(texts[i], states);
	}
}

GUI::GUI()
{
	
}

GUI::~GUI()
{
}

void GUI::Init(sf::Font * font, short textSize, int screenWidth, int screenHeight)
{
	m_font = font;
	m_textSize = textSize;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void GUI::UpdateStats(std::vector<Player*>* players)
{
	m_respawns.resize(players->size());

	for (short i = 0; i < players->size(); ++i)
	{
		m_respawns[i] = (*players)[i]->GetRespawnsCount();
	}
}

