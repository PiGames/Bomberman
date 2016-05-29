#include "LevelView.h"



LevelView::LevelView()
{
}


LevelView::~LevelView()
{
}


void LevelView::SetLevel(Level * level, sf::Texture * textures, const size_t & tileSize)
{
	m_data.resize(level->GetHeight());
	TILE_SIZE = tileSize;
	for (int y = 0; y < level->GetHeight(); ++y)
	{
		m_data[y].resize(level->GetWidth());
		for (int x = 0; x < level->GetWidth(); ++x)
		{
			m_data[y][x].setTexture(*textures);
			m_data[y][x].setTextureRect(sf::IntRect(static_cast<int>(tileSize*level->GetTile(x, y)), 0, static_cast<int>(tileSize), static_cast<int>(tileSize)));
			m_data[y][x].setPosition(static_cast<float>(x*tileSize), static_cast<float>(y*tileSize));
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

void LevelView::ChangeTileTextureToNone(size_t x, size_t y)
{
	m_data[y][x].setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
}
