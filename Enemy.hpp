#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "includes.hpp"

#include "Entity.hpp"
#include "Board.hpp"
#include "Hero.hpp"
#include "Settings.hpp"
#include "Gun.hpp"

class Enemy : public Entity
{
public:
	Enemy(void){};
	Enemy(sf::Texture& tex, Board& b, float x, float y, float w, float h, int health, int speed, int damage);
	
	Enemy& operator=(const Enemy& e);

	void moving(Board& b, Hero& p);

	bool is_open_pozition(Board& b);

	void shooting(Board& b, Hero& p, sf::Sound& shootSound, sf::Sound& rechargeSound, float cur_time);
	void bfs(Board& b, Hero& p);

	void draw(sf::RenderWindow& window) override;

	std::vector<std::pair<int, int>> path_to_player;
	int distance;
	int damage;
	bool saw_the_player, alive;

	sf::RectangleShape borderHealth, healthBar;

	Gun gun;

	bool wasRechargeSound = false; //нужно ли воспроизводить звук перезарядки
};

#endif