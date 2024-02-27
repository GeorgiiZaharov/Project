#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include "Entity.hpp"
#include "Board.hpp"
#include "Hero.hpp"
#include "Settings.hpp"
#include <SFML/Window.hpp>
#include <cmath>
#include <queue>
#include <algorithm>
#include "Gun.hpp"

class Enemy : public Entity
{
public:
	Enemy(void){};
	Enemy(sf::Texture& tex, Board& b, float x, float y, float w, float h);
	
	Enemy& operator=(const Enemy& e);

	void moving(Board& b, Hero& p);

	bool is_open_pozition(Board& b);

	void shooting(Board& b, Hero& p, float cur_time);
	void bfs(Board& b, Hero& p);

	void draw(sf::RenderWindow& window) override;

	std::vector<std::pair<int, int>> path_to_player;
	int distance;
	int damage;
	bool saw_the_player, alive;

	sf::RectangleShape borderHealth, healthBar;

	Gun gun;
};

#endif