#include "LevelView.h"



LevelView::LevelView()
{
}


LevelView::~LevelView()
{
}


void LevelView::SetLevel(Level * level, TextureAtlas* atlas)
{
	m_atlas = atlas;
	int tileSize = static_cast<int>(atlas->GetCellSizeX());
	m_data.resize(level->GetHeight());
	TILE_SIZE = tileSize;
	for (int y = 0; y < level->GetHeight(); ++y)
	{
		m_data[y].resize(level->GetWidth());
		for (int x = 0; x < level->GetWidth(); ++x)
		{
			atlas->SetSpriteTextureByIndex(m_data[y][x], static_cast<int>(level->GetTile(x, y)));
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

void LevelView::ChangeTileTexture(size_t x, size_t y, TT::TileType tileNumber)
{
	m_atlas->SetSpriteTextureByIndex(m_data[y][x], static_cast<int>(tileNumber));
}

