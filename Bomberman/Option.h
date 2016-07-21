#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <iostream>


class Option :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	bool isSelected(short & posX, short & posY);

public:
	/// Option constructor
	/// <param name = "fontPointer"> Pointer to font object </param>
	/// <param name = "optionNamePointer"> Pointer to std::string </param>
	/// <param name = "characterSize"> Character size of option inscription </param>
	/// <param name = "posX"> Position X (relative to upper-left corner) </param>
	/// <param name = "posY"> Position Y (relative to upper-left corner) </param>
	/// <param name = "buttonCol"> Button color </param>
	Option(sf::Font * fontPointer, std::string optionName, short characterSize, short posX, short posY, sf::Color buttonCol, sf::Color buttonSelected);
	~Option();

	void Update(short & mousePosX, short & mousePosY);

	bool IsClicked();

private:
	sf::Font * m_font;
	sf::RectangleShape m_rectangle;
	sf::Color m_buttonNormal;
	sf::Color m_buttonSelected;
	std::string m_optionName;
	bool m_selected;
	bool m_clicked;
	short m_characterSize;

};

