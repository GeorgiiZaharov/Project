#ifndef HERO_HPP
#define HERO_HPP

#include "includes.hpp"

#include "Entity.hpp"
#include "Board.hpp"
#include "Gun.hpp"
#include "Settings.hpp"

class Hero : public Entity
{
public:
	Hero(sf::Texture& tex, float x, float y, float w, float h, int health, int speed, int damage);
	Hero(void){};

	Hero& operator=(const Hero& h);

	void draw(sf::RenderWindow& window) override;

	void moving(Board& b);
	void shooting(float dx, float dy, sf::Sound& shootSound, sf::Sound& rechargeSound, float cur_time);

	int damage; 

	sf::RectangleShape borderHealth, healthBar;

	Gun gun;

	bool wasRechargeSound = false; //нужно ли воспроизводить звук перезарядки
};

#endif