#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Player.h"


class GUI:
	public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	GUI(sf::Font font, short textSize, int screenWidth, int screenHeight);
	~GUI();

	void UpdateStats(std::vector<Player> & players);

private:
	sf::Font m_font;
	short m_textSize;
	int m_screenWidth;
	int m_screenHeight;
	std::vector<short> m_respawns;

};

