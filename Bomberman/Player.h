#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicalBody.h"
#include "Animator.h"
#include "Bomb.h"


class Player : public sf::Drawable, public PhysicalBody
{
public:
	const int TILE_SIZE = 64;

	Player();
	~Player();


	/// Sets animator
	/// <param name="texture">animator</param>
	void SetAnimator(Animator& animator, size_t width, size_t height);
	

	/// Sets bomb ray texture
	/// <param name="texture">texture of ray</param>
	void SetBombRayTexture(sf::Texture * texture); // TODO: use animator
	
	
	/// Sets the player direction, possible values: -1, 0, 1
	/// <param name="x">direction x</param>
	/// <param name="y">direction y</param>
	void OnMoveKeyPressed(int x, int y);
	
	/// Sends the information about action key down (plant the bomb)
	void TryPlantingTheBomb();
	void SetBombTexture(sf::Texture * texture);
	
	void SetLevelPointer(Level * level);

	std::vector<sf::FloatRect> GetBombRaysColliders();
	//to chyba powinno byc prywatne
	void CheckIsPlayerInBombRay(std::vector<sf::FloatRect> * bombRays);

	/// Update player position, update states etc...
	/// <param name="dt">delta time in seconds</param>
	void Update(const float& dt);

private:
	Level * level;
	sf::Sprite m_sprite;
	Animator* m_animator;

	Bomb * m_bomb;
	sf::Texture * m_bombTexture;
	sf::Texture * m_bombRayTexture;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void reactWhenIsInBombRay();
};

