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
	return false;
}


TT::TileType Level::GetTile(size_t x, size_t y)
{
	return TT::TileType();
}


size_t Level::GetWidth() const
{
	return m_width;
}


size_t Level::GetHeight() const
{
	return m_height;
}
