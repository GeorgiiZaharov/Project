#include "Gun.hpp"

Gun::Gun(int magazine_size, float bullet_duration, int speed_bullet, float recharge_time){
	this->magazine_size = magazine_size;
	this->bullet_duration = bullet_duration;
	this->speed_bullet = speed_bullet;
	this->bullets_in_gun = magazine_size;
	this->recharge_time = recharge_time;


	for (int i = 0; i < bullets_in_gun; ++i){
		this->magazine.push_back(Bullet());
	}
}

Gun& Gun::operator=(const Gun& g){
	this->bullets_in_gun = g.bullets_in_gun;
	this->magazine_size = g.magazine_size;
	this->last_shoot_time = g.last_shoot_time;
	this->bullet_duration = g.bullet_duration;
	this->speed_bullet = g.speed_bullet;
	this->recharge_time = g.recharge_time;

	this->magazine.clear();
	this->magazine = g.magazine;
	return *this;
}

bool Gun::ready(float cur_time){
	// std::cout<<cur_time<<std::endl;
	if (bullets_in_gun && cur_time - last_shoot_time >= bullet_duration) return true;
	return false;
}

int Gun::shoot(float x, float y, float dx, float dy, float cur_time){//1 - выстрел, 0 - перезарядка
	if (ready(cur_time)){
		this->magazine[magazine_size - bullets_in_gun] = Bullet(
		    3, 3,//height and weight sprite
		    x,//координаты старта
		    y,//координаты старта
		    dx,//направление
		    dy,//направление
		    6//скорость
		);
		--bullets_in_gun;
		this->last_shoot_time = cur_time;
		return 1;
	}
	else if (bullets_in_gun == 0){
		if (cur_time - last_shoot_time >= recharge_time)
			bullets_in_gun = magazine_size;
		return 0;
	}
	return -1;
}

void Gun::draw(sf::RenderWindow& window){
	for (int i = 0; i < magazine_size - bullets_in_gun; ++i){
		magazine[i].draw(window);
	}
}