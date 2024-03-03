#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "includes.hpp"

class Entity
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
	void rotate(float dx, float dy);
	sf::Sprite rec;
	sf::Texture* tex;
	int poz_x, poz_y;
	float dx, dy;
	int speed;
	int health, max_health;
};

#endif