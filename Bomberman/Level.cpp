#include "Level.h"



Level::Level()
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
