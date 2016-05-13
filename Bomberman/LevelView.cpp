#include "LevelView.h"



LevelView::LevelView()
{
}


LevelView::~LevelView()
{
}


void LevelView::SetLevel(Level * level, sf::Texture * textures, const size_t & tileSize)
{
	m_data.resize[level->GetHeight()];

	for (int y = 0; y < level->GetHeight(); ++y)
	{
		m_data[y].resize(level->GetWidth());
		for (int x = 0; x < level->GetWidth(); ++x)
		{
			m_data[y][x].setTexture(*textures);
			m_data[y][x].setTextureRect(sf::IntRect(tileSize*level->GetTile(x, y), 0, tileSize, tileSize));
			m_data[y][x].setPosition(x*tileSize, y*tileSize);
		}
	}
}


void LevelView::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int y = 0; y < m_data.size(); ++y)
	{
		for (int x = 0; x < m_data[0].size(); ++x)
		{
			target.draw(m_data[y][x]);
		}
	}
}
