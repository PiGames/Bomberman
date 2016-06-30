#include "Option.h"


void Option::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Text optionText(m_optionName, *m_font, m_characterSize);
	optionText.setPosition(m_rectangle.getPosition().x, m_rectangle.getPosition().y);
	
	target.draw(m_rectangle, states);
	target.draw(optionText);
}

Option::Option(sf::Font * fontPointer, std::string optionName, short characterSize, short posX, short posY, sf::Color buttonCol, sf::Color buttonSelected)
{
	sf::Text tempText(optionName, *fontPointer, characterSize);
	m_font = fontPointer;
	m_optionName = optionName;
	m_characterSize = characterSize;
	m_rectangle.setPosition(posX, posY);
	m_rectangle.setSize(sf::Vector2f(tempText.getGlobalBounds().width, tempText.getGlobalBounds().height * 1.8));
	m_rectangle.setFillColor(buttonCol);
	m_buttonNormal = buttonCol;
	m_buttonSelected = m_buttonSelected;
}

Option::~Option()
{
}

bool Option::isSelected(short & posX, short & posY)
{
	return m_rectangle.getGlobalBounds().contains(posX, posY);
}

void Option::Update(short & mousePosX, short & mousePosY)
{
	m_clicked = (isSelected(mousePosX, mousePosY) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ? true : false);
	m_selected = isSelected(mousePosX, mousePosY);

	if (m_selected)
	{
		m_rectangle.setFillColor(m_buttonSelected);
	}
	else
	{
		m_rectangle.setFillColor(m_buttonNormal);
	}
}

bool Option::IsClicked()
{
	return m_clicked;
}
