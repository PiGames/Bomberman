#include "TextureAtlas.h"



TextureAtlas::TextureAtlas()
{
}


TextureAtlas::~TextureAtlas()
{
}


bool TextureAtlas::LoadFromFile(const std::string & path)
{
	if (!m_texture.loadFromFile(path))
		return false;
	else
		return true;
}


bool TextureAtlas::TrimByGrid(const size_t & cellSizeX, const size_t & cellSizeY)
{
	m_cellSizeX = cellSizeX;
	m_cellSizeY = cellSizeY;

	m_textureSizeX = m_texture.getSize().x / m_cellSizeX;

	m_count = (m_texture.getSize().x / m_cellSizeX) * (m_texture.getSize().y / m_cellSizeY);

	if ((m_texture.getSize().x % m_cellSizeX == 0) && m_texture.getSize().y % m_cellSizeY == 0)
	{
		return true;
	}
	else
		return false;
}


size_t TextureAtlas::GetCount() const
{
	return m_count;
}


size_t TextureAtlas::GetCellSizeX() const
{
	return m_cellSizeX;
}


size_t TextureAtlas::GetCellSizeY() const
{
	return m_cellSizeY;
}


void TextureAtlas::SetSpriteTextureByIndex(sf::Sprite & sprite, size_t index)
{
	size_t m_index = m_cellSizeX * index;

	if (m_index > m_textureSizeX)
	{
		size_t buffer = 0;
		for (int i = 1; i < index; i++)
		{
			if (i >= m_textureSizeX)
				buffer += 1;
		}
		size_t m_downTextureSet = m_cellSizeY *= buffer;
		sprite.setTextureRect(sf::IntRect(static_cast<int>(m_index), static_cast<int>(m_downTextureSet), static_cast<int>(m_cellSizeX), static_cast<int>(m_cellSizeY)));
	}
	else if (m_index <= m_textureSizeX)
		sprite.setTextureRect(sf::IntRect(static_cast<int>(m_index), 0, static_cast<int>(m_cellSizeX), static_cast<int>(m_cellSizeY)));
	else
		sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_cellSizeX), static_cast<int>(m_cellSizeY)));
}
