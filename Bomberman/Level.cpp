#include "Level.h"



Level::Level()
{
}


Level::~Level()
{
}


bool Level::LoadFromFile(const std::string & path)
{
	// TODO wczytywanie danych z pliku do m_data
	/*
		Przyk³adowy poziom znajduje siê w "data/sample_level.txt"
		TileType jest zdefiniowane w "Types.h"

		Funkcja powinna zwracaæ true je¿eli uda³o siê wczytaæ poziom
		je¿eli np. wersja kompatybilnoœci jest niewspierana, magic header jest inny to nale¿y zwróciæ fa³sz

		specyfikacja poziomu znajduje siê w "todo.txt"

		HINT: stwóz tablicê któej pierwsza wspó³rzêdna to y, a nie x
	*/
	std::fstream file(path, std::ios::in);
	if (!file.is_open())
		return false;

	std::string data;
	file >> data; // skip header
	file >> data; // skip version

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
			m_data[i][j] = TT::TileType(raw);
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
