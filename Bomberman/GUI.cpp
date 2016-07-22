#include "GUI.h"


void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	rect->setFillColor(sf::Color(255, 255, 255, 155));
	rect->setSize(sf::Vector2f(m_screenWidth, m_screenHeight));
	if (m_endOfGameMenuView)
	{
		target.draw(*m_frame, states);
		target.draw(*rect, states);

		target.draw(*m_returnToMenuButton->GetSpritePointer(), states);
		target.draw(*m_returnToMenuButton->GetTextPointer(), states);

		target.draw(*m_playAgainButton->GetSpritePointer(), states);
		target.draw(*m_playAgainButton->GetTextPointer(), states);

		target.draw(*m_exitButton->GetSpritePointer(), states);
		target.draw(*m_exitButton->GetTextPointer(), states);

		target.draw(*m_winnerText);
	}
	if (m_gameGUIView)
	{
		target.draw(*m_playerOneLives);
		target.draw(*m_playerSecondLives);
	}

}

GUI::GUI()
{
}

GUI::~GUI()
{
	delete rect;

	delete m_returnToMenuButton;
	delete m_playAgainButton;
	delete m_exitButton;

	delete m_frameTexture;
	delete m_frame;

	delete m_winnerText;

	delete m_playerOneLives;
	delete m_playerSecondLives;
}

void GUI::Init(sf::Font * font, short textSize, int screenWidth, int screenHeight, bool* playAgain, bool* exit, bool* enterMenu)
{
	rect = new sf::RectangleShape();

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;;

	m_playerOneLives = new sf::Text();
	m_playerOneLives->setFont(*font);
	m_playerOneLives->setString("Player 1 Lives: 3");
	m_playerOneLives->setPosition(sf::Vector2f(20, 10));
	m_playerOneLives->setColor(sf::Color(255, 255, 255));
	m_playerOneLives->setScale(1.2f, 1.2f);


	m_playerSecondLives = new sf::Text();
	m_playerSecondLives->setFont(*font);
	m_playerSecondLives->setString("Player 2 Lives: 3");
	m_playerSecondLives->setPosition(sf::Vector2f(screenWidth-300, screenHeight-50));
	m_playerSecondLives->setColor(sf::Color(255, 255, 255));
	m_playerSecondLives->setScale(1.2f, 1.2f);


	m_whoWin = -1;

	m_enterMenu = enterMenu;
	m_exit = exit;
	m_playAgain = playAgain;

	m_endOfGameMenuView = false;
	m_gameGUIView = true;

	m_frameTexture = new sf::Texture();
	m_frameTexture->loadFromFile("data/frame.png");
	m_frame = new sf::Sprite();
	m_frame->setTexture(*m_frameTexture);
	m_frame->setScale((float)m_frameTexture->getSize().x / (float)(screenWidth * 5), (float)m_frameTexture->getSize().y / (float)(screenHeight * 7));
	m_frame->setPosition(screenWidth / 2.f - (m_frameTexture->getSize().x * m_frame->getScale().x)/2.f, screenHeight / 3.3f - 50);

	m_returnToMenuButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 2.3f - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Return to Menu");
	m_playAgainButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 1.7f -50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Play Again");
	m_exitButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 1.7f + screenHeight / 1.7f - screenHeight / 2.3f - 50), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Exit Game");

	m_winnerText = new sf::Text();
	m_winnerText->setFont(*font);
	m_winnerText->setString("Player 1 Wins!");
	sf::FloatRect textRect = m_winnerText->getLocalBounds();
	m_winnerText->setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_winnerText->setPosition(sf::Vector2f(screenWidth / 2.f,m_frame->getPosition().y+20));
	m_winnerText->setColor(sf::Color(0.f, 107, 139));
	m_winnerText->setScale(1.2f, 1.2f);
}

void GUI::UpdateStats(std::vector<Player*>* players, short mouseX, short mouseY)
{
	m_endOfGameMenuView = false;
	m_gameGUIView = true;
	for (short i = 0; i < players->size(); ++i)
	{
		switch (i)
		{
		case 0:
			m_playerOneLives->setString("Player 1 Lives: " + std::to_string((*players)[i]->GetRespawnsCount()));
		case 1:
			m_playerSecondLives->setString("Player 2 Lives: " + std::to_string((*players)[i]->GetRespawnsCount()));
		}

		if ((*players)[i]->GetWin())
		{
			m_whoWin = i;
			m_winnerText->setString("Player "+ std::to_string(m_whoWin+1)+" Wins!");
			break;
		}
		else
		{

		}

	}

}

void GUI::UpdateStats(std::vector<Player*>* players, short mouseX, short mouseY, bool & playAgain, bool & exit, bool & enterMenu)
{
	UpdateStats(players, mouseX, mouseY);
	m_endOfGameMenuView = true;
	m_gameGUIView = false;
}

void GUI::processEvents(sf::Vector2i mousePos, sf::Event* eventPointer)
{
	if (m_endOfGameMenuView)
	{
		if (eventPointer->type == sf::Event::MouseButtonReleased && eventPointer->mouseButton.button == sf::Mouse::Left)
		{
			m_returnToMenuButton->Update(mousePos, false);
			m_playAgainButton->Update(mousePos, false);
			m_exitButton->Update(mousePos, false);

			if (m_returnToMenuButton->GetSpritePointer()->getGlobalBounds().contains((sf::Vector2f)mousePos))
			{
				*m_playAgain = false;
				*m_enterMenu = true;
				*m_exit = true;
			}
			if (m_playAgainButton->GetSpritePointer()->getGlobalBounds().contains((sf::Vector2f)mousePos))
			{
				*m_playAgain = true;
				*m_enterMenu = false;
				*m_exit = false;
			}
			if (m_exitButton->GetSpritePointer()->getGlobalBounds().contains((sf::Vector2f)mousePos))
			{
				*m_playAgain = false;
				*m_enterMenu = false;
				*m_exit = true;
			}

		}
		if (eventPointer->type == sf::Event::MouseButtonPressed && eventPointer->mouseButton.button == sf::Mouse::Left)
		{
			m_returnToMenuButton->Update(mousePos, true);
			m_playAgainButton->Update(mousePos, true);
			m_exitButton->Update(mousePos, true);
		}
	}

}
