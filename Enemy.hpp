#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "Board.hpp"
#include "Entity.hpp"
#include "Hero.hpp"
#include "Settings.hpp"
#include <SFML/Window.hpp>
#include <cmath>
#include <queue>
#include <algorithm>

class Enemy : public Entity
{
public:
	Enemy(void){};
	Enemy(const Board& b, float x, float y, float w, float h);
	
	Enemy& operator=(const Enemy& e);

	void moving(Board& b, Hero& p);
	void bfs(Board& b, Hero& p);

	std::vector<std::pair<int, int>> path_to_player;
	int distance;
	float damage;
};

#endif