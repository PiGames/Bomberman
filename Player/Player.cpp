#include "Player.h"



Player::Player()
{
}

Player::~Player()
{
}

void Player::move(int x, int y)
{
	sprite.move(x, y);
}
void Player::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}
void Player::setTexture()
{
	texture.loadFromFile("data/player.png");
	sprite.setTexture(texture);
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

float Player::getPosX()
{
	return sprite.getPosition().x;
}

float Player::getPosY()
{
	return sprite.getPosition().y;
}
