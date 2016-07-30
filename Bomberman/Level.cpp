#include "Level.h"



Level::Level()
	:m_destroyableTilesKey(0)
{
}


Level::~Level()
{
}


bool Level::LoadFromFile(const std::string & path)
{
	std::fstream file(path, std::ios::in);
	if (!file.is_open())
		return false;

	std::string data;
	file >> data;
	if (data != MAGIC_HEADER)
		return false;

	float version;
	file >> version;
	if (version != m_version)
		return false; // HACK temporary only

	file >> m_width;
	file >> m_height;

	m_data.resize(m_height);
	for (unsigned int i = 0; i < m_height; ++i)
		m_data[i].resize(m_width);

	int raw;
	for (unsigned int i = 0; i < m_height; ++i)
	{
		for (unsigned int j = 0; j < m_width; ++j)
		{
			file >> raw;
			m_data[i][j] = static_cast<TT::TileType>(raw);
		}
	}
	return true;
}


TT::TileType Level::GetTile(size_t x, size_t y)
{
	return m_data[y][x];
}


size_t Level::GetWidth() const
{
	return m_width;
}


size_t Level::GetHeight() const
{
	return m_height;
}

bool Level::DestroyTile(size_t x, size_t y, bool destroyTexture)
{
	if(m_data[y][x] <= TT::TileType::NONE_WITH_SHADOW)
		return false;

	if (m_data[y - 1][x] >= TT::TileType::WEAK_WALL && m_data[y - 1][x] != TT::TileType::BOMB)
	{
		m_data[y][x] = TT::TileType::NONE_WITH_SHADOW;
		m_view->ChangeTileTexture(x, y, TT::TileType::NONE_WITH_SHADOW);
	}	
	else
	{
		m_data[y][x] = TT::TileType::NONE;
		m_view->ChangeTileTexture(x, y, TT::TileType::NONE);
	}

	if (m_data[y + 1][x] == TT::TileType::NONE_WITH_SHADOW)
	{
		m_data[y+1][x] = TT::TileType::NONE;
		m_view->ChangeTileTexture(x, y+1, TT::TileType::NONE);
	}
	if (m_data[y - 1][x] == TT::TileType::DOUBLE_WEAK_WALL)
	{
		m_data[y - 1][x] = TT::TileType::WEAK_WALL;
		m_view->ChangeTileTexture(x, y - 1, TT::TileType::WEAK_WALL);
	}
	if (m_data[y - 1][x] == TT::TileType::DOUBLE_INDESTRUCTIBLE_WALL)
	{
		m_data[y - 1][x] = TT::TileType::INDESTRUCTIBLE_WALL;
		m_view->ChangeTileTexture(x, y - 1, TT::TileType::INDESTRUCTIBLE_WALL);
	}
	if (m_data[y - 1][x] == TT::TileType::HALF_INDESTRUCTIBLE_WALL)
	{
		m_data[y - 1][x] = TT::TileType::INDESTRUCTIBLE_WALL;
		m_view->ChangeTileTexture(x, y - 1, TT::TileType::INDESTRUCTIBLE_WALL);
	}
	return true;
	
}

void Level::SetTileAsBomb(size_t x, size_t y)
{
	m_data[y][x] = TT::TileType::BOMB;
}

void Level::SetTileAsDestroyable(size_t x, size_t y)
{
	m_data[y][x] = TT::TileType::WEAK_WALL;
}

void Level::SetLevelView(LevelView * view)
{
	m_view = view;
}
