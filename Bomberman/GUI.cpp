#include "GUI.h"


void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_endOfGameMenuView)
	{
	target.draw(*m_frame, states);

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

	}

}

GUI::GUI()
{
}

GUI::~GUI()
{

}

void GUI::Init(sf::Font * font, short textSize, int screenWidth, int screenHeight, bool* playAgain, bool* exit, bool* enterMenu)
{
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
	m_frame->setPosition(screenWidth / 2.f - (m_frameTexture->getSize().x * m_frame->getScale().x)/2.f, screenHeight / 3.3f);

	m_returnToMenuButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 2.3f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Return to Menu");
	m_playAgainButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 1.7f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Play Again");
	m_exitButton = new Button(sf::Vector2f(screenWidth / 2 - 150, screenHeight / 1.7f + screenHeight / 1.7f - screenHeight / 2.3f), sf::Vector2i(300, 75.f), "data/pressButton.png", "data/unpressButton.png", "Exit Game");

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
		if ((*players)[i]->GetWin())
		{
		}
		else
		{
			
		}

	}

}

void GUI::UpdateStats(std::vector<Player*>* players, short mouseX, short mouseY, bool & playAgain, bool & exit, bool & enterMenu)
{
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


