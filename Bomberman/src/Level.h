#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "Types.h"
#include <map>
#include <iostream>
#include "LevelView.h"

#define MAGIC_HEADER "BOMBERMAN_LEVEL"

class LevelView;

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

	/// Get level height in tiles
	/// <returns>Height</returns>
	size_t GetHeight() const;

	///Changes particular tile's type
	/// <param="x">x'th index</param>
	/// <param="y">y'th index</param>
	/// <returns>True if tile can be destroyed</returns>
	/// <returns>False if cannot be destroyed</returns>
	bool DestroyTile(size_t x, size_t y, bool destroyTexture=true);
	void SetTileAsDestroyable(size_t x, size_t y);
	void SetTileAsBomb(size_t x, size_t y);

	void SetLevelView(LevelView* view);

private:
	size_t m_width;
	size_t m_height;
	LevelView* m_view;
	const float m_version = 1.0f;

	std::vector< std::vector<TT::TileType> > m_data;

	std::map<int, std::pair<int, int> > m_destroyableTiles;
	int m_destroyableTilesKey;

	std::map<int, std::pair<int, int> >::iterator getIteratorByValue(std::pair<int,int>);
	
};

