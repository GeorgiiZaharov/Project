#ifndef GUN_HPP
#define GUN_HPP 

#include "includes.hpp"

#include "Bullet.hpp"

class Gun{
public:
	Gun(){}
	Gun(const Gun& g);
	Gun(sf::Texture& tex, int magazine_size, float bullet_duration, int speed_bullet, float recharge_time);

	Gun& operator=(const Gun& g);
	
	bool is_recharging(float cur_time);
	int get_nbullets(float cur_time);
	bool ready(float cur_time);
	int shoot(float x, float y, float dx, float dy, float cur_time);//1 - выстрел, 0 - перезарядка, -1 - иначе
	void draw(sf::RenderWindow& window);

	int bullets_in_gun, magazine_size, speed_bullet;
	float last_shoot_time, bullet_duration, recharge_time;
	std::vector<Bullet> magazine;
	sf::Texture* tex;
};

#endif