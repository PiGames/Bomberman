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

		texts.push_back(tempText);
		target.draw(texts[i], states);
	}

	if (m_whoWin.second)
	{
		sf::Text winText;
		sf::Text playAgain;
		sf::RectangleShape thing;
		thing.setSize(sf::Vector2f(m_screenWidth, m_screenHeight));
		thing.setFillColor(sf::Color(255, 255, 255, 200));

		winText.setFont(*m_font);
		winText.setCharacterSize(m_textSize);
		winText.setColor(sf::Color::Black);
		winText.setString("Player " + std::to_string(m_whoWin.first) + " win!");
		winText.setPosition(m_screenWidth / 2 - winText.getGlobalBounds().width, m_screenHeight / 2 - winText.getGlobalBounds().height);
	
		playAgain = winText;
		playAgain.setString("To play again press ENTER, to exit press ESC.");
		playAgain.setPosition(0, playAgain.getPosition().y + playAgain.getGlobalBounds().height * 1.1);

		target.draw(thing, states);
		target.draw(winText, states);
		target.draw(playAgain, states);
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
		if ((*players)[i]->GetWin())
		{
			m_whoWin.first = i;
			m_whoWin.second = true;
			break;
		}
		else
		{
			m_whoWin.second = false;
		}
	}
}


