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
		Przyk�adowy poziom znajduje si� w "data/sample_level.txt"
		TileType jest zdefiniowane w "Types.h"

		Funkcja powinna zwraca� true je�eli uda�o si� wczyta� poziom
		je�eli np. wersja kompatybilno�ci jest niewspierana, magic header jest inny to nale�y zwr�ci� fa�sz

		specyfikacja poziomu znajduje si� w "todo.txt"

		HINT: stw�z tablic� kt�ej pierwsza wsp�rz�dna to y, a nie x
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
