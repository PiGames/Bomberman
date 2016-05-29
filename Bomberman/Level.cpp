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
	for (int i = 0; i < m_height; ++i)
		m_data[i].resize(m_width);

	int raw;
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			file >> raw;
			m_data[i][j] = static_cast<TT::TileType>(raw);
			if (m_data[i][j] == TT::TileType::WEAK_WALL)
				m_destroyableTiles[m_destroyableTilesKey++] = std::pair<int,int>(j,i);
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

bool Level::DestroyTile(size_t x, size_t y)
{
	if(m_data[y][x] == TT::TileType::INDESTRUCTIBLE_WALL || m_data[y][x] == TT::TileType::NONE)
		return false;

	m_data[y][x] = TT::TileType::NONE;
	m_destroyableTiles.erase(getIteratorByValue(std::pair<int, int>(x,y)));
	m_view->ChangeTileTextureToNone(x, y);
	return true;
	
}

void Level::SetLevelView(LevelView & view)
{
	m_view = &view;
}

std::map<int, std::pair<int, int> >::iterator Level::getIteratorByValue(std::pair<int, int> coords)
{
	std::map<int, std::pair<int, int> >::iterator it;

	for (it = m_destroyableTiles.begin(); it != m_destroyableTiles.end(); ++it)
		if (it->second == coords)
			return it;
}


