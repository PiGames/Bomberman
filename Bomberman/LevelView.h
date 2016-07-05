#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"
#include "TextureAtlas.h"

class Level;

class LevelView : public sf::Drawable
{
public:
	LevelView();
	~LevelView();

	/// Setups tiles
	/// <param="level>ptr to previosuly loaded level with tile data</param>
	/// <param="textures">ptr to texture atlas</param>
	/// <param="tileSize">size of tile in px</param>
	void SetLevel(Level* level, TextureAtlas* atlas);
	
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void ChangeTileTexture(size_t x, size_t y, TT::TileType tileNumber);
private:
	std::vector < std::vector<sf::Sprite> > m_data;
	int TILE_SIZE;
	TextureAtlas * m_atlas;
	int size;
};

