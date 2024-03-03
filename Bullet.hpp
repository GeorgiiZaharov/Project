#ifndef BULLET_HPP
#define BULLET_HPP

#include "includes.hpp"
#include "Entity.hpp"
#include "Board.hpp"

class Bullet : public Entity{
public:
	Bullet();
	Bullet(sf::Texture& tex, float w, float h, float x, float y, float dx, float dy, int speed);
	Bullet& operator=(const Bullet& b);
	bool check_collision(sf::FloatRect rec);
	bool check_collision(Board& b);
	void moving();
	void draw(sf::RenderWindow& window) override;

	bool was_collision;
};

#endif