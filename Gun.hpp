#ifndef GUN_HPP
#define GUN_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <vector>
#include "Bullet.hpp"

class Gun{
public:
	Gun(){}
	Gun(int magazine_size, float bullet_duration, int speed_bullet, float recharge_time);

	Gun& operator=(const Gun& g);
	
	bool ready(float cur_time);
	int shoot(float x, float y, float dx, float dy, float cur_time);//1 - выстрел, 0 - перезарядка, -1 - иначе
	void draw(sf::RenderWindow& window);

	int bullets_in_gun, magazine_size, speed_bullet;
	float last_shoot_time, bullet_duration, recharge_time;
	std::vector<Bullet> magazine;
};

#endif