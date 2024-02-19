#ifndef HERO_HPP
#define HERO_HPP

#include "Board.hpp"
#include "Entity.hpp"
#include "Settings.hpp"
#include <SFML/Window.hpp>

class Hero : public Entity
{
public:
	Hero(float x, float y, float w, float h);
	Hero(void);

	Hero& operator=(const Hero& h);

	void moving(Board& b, int w, int h);
	
	float vx, vy;
	float speed;

};

#endif