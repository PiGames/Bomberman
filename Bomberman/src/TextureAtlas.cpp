#include "TextureAtlas.h"



TextureAtlas::TextureAtlas()
{
	m_count = 0;
	m_cellWidth = m_cellHeight = 0;
	m_rows = m_columns = 0;
}


TextureAtlas::~TextureAtlas()
{
}


bool TextureAtlas::LoadFromFile(const std::string & path)
{
	if (!m_texture.loadFromFile(path))
	{
		m_count = 0;
		m_cellWidth = m_cellHeight = 0;
		m_rows = m_columns = 0;

		return false;
	}
	
	m_count = 1;
	m_cellWidth = m_texture.getSize().x;
	m_cellHeight = m_texture.getSize().y;
	m_rows = m_columns = 1;

	return true;
}


bool TextureAtlas::TrimByGrid(size_t cellSizeX, size_t cellSizeY)
{
	if (m_cellWidth % cellSizeX != 0 || m_cellHeight % cellSizeY != 0)
		return false;

	m_rows = m_cellWidth / cellSizeX;
	m_columns = m_cellHeight / cellSizeY;

	m_count = m_rows * m_columns;
	m_cellWidth = cellSizeX;
	m_cellHeight = cellSizeY;

	return true;
}


size_t TextureAtlas::GetCount() const
{
	return m_count;
}


size_t TextureAtlas::GetCellSizeX() const
{
	return m_cellWidth;
}


size_t TextureAtlas::GetCellSizeY() const
{
	return m_cellHeight;
}


void TextureAtlas::SetSpriteTextureByIndex(sf::Sprite & sprite, size_t index)
{
	if (m_count == 0 || index >= m_count)
		return;

	int x = static_cast<int>(index % (m_rows) * m_cellWidth);
	int y = static_cast<int>(index / (m_rows) * m_cellHeight);

	sprite.setTexture(m_texture);
	sprite.setTextureRect(sf::IntRect(x, y, static_cast<int>(m_cellWidth), static_cast<int>(m_cellHeight)));
}
