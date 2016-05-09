#include "LevelView.h"



LevelView::LevelView()
{
}


LevelView::~LevelView()
{
}


void LevelView::SetLevel(Level * level, sf::Texture * textures, const size_t & tileSize)
{
	// TODO ustawienie spriteów do m_data
	// HINT: use setTextureRect
}


void LevelView::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int y = 0; y < m_data.size(); ++y)
	{
		for (int x = 0; x < m_data[y].size(); ++x)
		{
			target.draw(m_data[y][x]);
		}
	}
}
