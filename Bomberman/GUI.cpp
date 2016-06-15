#include "GUI.h"


void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::vector<sf::Text> texts;
	sf::Text tempText;
	tempText.setFont(m_font);
	tempText.setCharacterSize(m_textSize);
	tempText.setPosition(0, 0);

	for (short i = 0; i < m_respawns.size(); ++i)
	{
		// issue with displaying may cause this
		tempText.setString(static_cast<char>(m_respawns[i]));

		if (i)
		{
			if (i == 1)
			{
				tempText.setPosition(tempText.getPosition().x + m_screenWidth - tempText.getGlobalBounds().width, tempText.getPosition().y);
			}
			else //if (i == 2)
			{
				tempText.setPosition(tempText.getPosition().x - m_screenWidth + tempText.getGlobalBounds().width, tempText.getPosition().y + m_screenHeight - tempText.getGlobalBounds().height);
			}
		}

		texts.push_back(tempText);
		target.draw(texts[i], states);
	}
}

GUI::GUI(sf::Font font, short textSize, int screenWidth, int screenHeight)
{
	m_font = font;
	m_textSize = textSize;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

GUI::~GUI()
{
}

void GUI::UpdateStats(std::vector<Player>& players)
{
	m_respawns.resize(players.size());

	for (short i = 0; i < players.size(); ++i)
	{
		m_respawns[i] = players[i].GetRespawnsCount();
	}
}

