#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>
#include <string>


class TextureAtlas
{
public:
	TextureAtlas();
	~TextureAtlas();


	/// Load texture to memory from path
	/// <param name="path">relative or absolute path to texture</param>
	/// <returns>true OK</returns>
	/// <returns>false cannot load texture</returns>
	bool LoadFromFile(const std::string& path);
	

	/// Trims texture to smaller textures
	/// <param name="cellSizeX>cell width (px)</param>
	/// <param name="cellSizeY>cell height (px)</param>
	/// <returns>true OK</returns>
	/// <returns>true cannot trim texture</returns>
	bool TrimByGrid(const size_t& cellSizeX, const size_t& cellSizeY);
	
	
	/// Get total amount of textures
	/// <returns>Amount of subtextures</returns>
	size_t GetCount() const;
	
	
	/// Get width of single cell in pixels
	/// <returns>Cell's Width</returns>
	size_t GetCellSizeX() const;
	
	
	/// Get Size of single cell in pixels
	/// <returns>Cell's Height</returns>
	size_t GetCellSizeY() const;
	
	
	/// Sets appropiate texture rect selected by index
	/// <param name="sprite">reference to sprite</param>
	/// <param name="index">index of texture to change</param>
	void SetSpriteTextureByIndex(sf::Sprite& sprite, size_t index=0);

private:
	// TODO miejsce na twoje pola / metody prywatne
};

