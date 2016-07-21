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
	void Init(Level* level, std::vector<Player*>* players);
	void Update(float dt);
private:
	void gatherBombInformation();
	void handleBombKicking(float dt);
	void checkBombsAfterExplosionsCollisions();
	std::map<std::pair<int*, int*>, Bomb*> bombs;
	std::map<std::pair<int*, int*>, Bomb*>::iterator it;
	std::vector<Player*>* m_players;
	std::vector<Ray*>rays;
	Level* m_level;
};

