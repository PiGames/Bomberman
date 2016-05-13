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

	size_t w = level->GetWidth();
	size_t h = level->GetHeight();

	m_data.resize(h);
	for (int i = 0; i < h; ++i)
		m_data[i].resize(w);

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			m_data[i][j].setTexture(*textures);
			m_data[i][j].setTextureRect(sf::IntRect(tileSize*level->GetTile(j, i), 0, tileSize, tileSize));
			m_data[i][j].setPosition(j*tileSize, i*tileSize);
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
