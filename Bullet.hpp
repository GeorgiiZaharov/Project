#ifndef BULLET_HPP
#define BULLET_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Board.hpp"

class Bullet : public Entity{
public:
	Bullet();
	Bullet(float w, float h, float x, float y, float dx, float dy, int speed);
	// Bullet(const float w, const float h, const float x, const float y, const float dx, const float dy, const int speed);
	Bullet& operator=(const Bullet& b);
	bool check_collision(sf::FloatRect rec);
	bool check_collision(Board& b);
	void moving(void);
	void draw(sf::RenderWindow& window) override;

	bool was_collision;
};

#endif