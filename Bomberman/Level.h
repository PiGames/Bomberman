#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "Types.h"

#define MAGIC_HEDER "BOMBERMAN_LEVEL"

class Level
{
public:
	Level();
	~Level();

	/// Loads level from file
	/// <param="path"> absolute or relative path to level</param>
	/// <returns>True if loaded file</returns>
	/// <returns>False if something went wrong</returns>
	bool LoadFromFile(const std::string& path);
	
	/// Get Tile Type at index (x,y)
	/// <param="x">x'th index</param>
	/// <param="y">y'th index</param>
	/// <returns>TileType object</returns>
	TT::TileType GetTile(size_t x, size_t y);

	/// Get level width in tiles
	/// <returns>Width</returns>
	size_t GetWidth() const;

	/// Get level hwight in tiles
	/// <returns>Height</returns>
	size_t GetHeight() const;

private:
	size_t m_width;
	size_t m_height;

	const float m_version = 1.0f;

	std::vector< std::vector<TT::TileType> > m_data;
};

