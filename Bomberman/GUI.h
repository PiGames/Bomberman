#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Player.h"
#include "Option.h"


class GUI:
	public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	GUI();
	~GUI();
	void Init(sf::Font* font, short textSize, int screenWidth, int screenHeight);
	void UpdateStats(std::vector<Player*> * players, short mouseX, short mouseY);
	void UpdateStats(std::vector<Player*> * players, short mouseX, short mouseY, bool & playAgain, bool & exit, bool & enterMenu);

private:
	sf::Font * m_font;
	short m_textSize;
	int m_screenWidth;
	int m_screenHeight;
	std::vector<short> m_respawns;
	// player id, win?
	std::pair<short, bool> m_whoWin;

	Option * m_optionPlayAgain;
	Option * m_optionExit;
	Option * m_optionReturnMenu;
};

