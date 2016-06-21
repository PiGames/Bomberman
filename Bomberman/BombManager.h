#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Player.h"

class BombManager
{
public:
	BombManager();
	~BombManager();
	void Init(std::vector<Player*>* players);
	void Update();
private:
	std::map<std::pair<int, int>, Bomb*> bombs;
	std::map<std::pair<int, int>, Bomb*>::iterator bomb;
	std::vector<Player*>* m_players;
	std::vector<PhysicalBody*>rays;
};

