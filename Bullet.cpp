#include "Bullet.hpp"

Bullet::Bullet(){
	was_collision = false;
}

Bullet::Bullet(float w, float h, float x, float y, float dx, float dy, int speed){

	float len_direct = static_cast<float>(std::sqrt(dx * dx + dy * dy));
	this->dx = dx / len_direct;
	this->dy = dy / len_direct;

	this->rec = sf::RectangleShape(sf::Vector2f(w, h));
	this->rec.setPosition(x, y);
	this->rec.setFillColor(sf::Color::Yellow);
	//rotate
	this->rec.setOrigin(w/2, h/2);
	this->rec.move(w/2, h/2);
	this->rec.rotate(std::atan2(dy, dx)); /////////////////////////////////////////


	this->speed = speed;

	this->was_collision = false;
}



Bullet& Bullet::operator=(const Bullet& b){
	this->rec = b.rec;
	this->poz_x = b.poz_x;
	this->poz_y = b.poz_y;

	this->dx = b.dx;
	this->dy = b.dy;
	this->speed = b.speed;
	this->was_collision = b.was_collision;
	return *this;
}

bool Bullet::check_collision(sf::FloatRect rec){
	if (this->rec.getGlobalBounds().intersects(rec)){
		was_collision = true;
		return true;
	}
	return false;
}

bool Bullet::check_collision(Board& b){
	if (b.check_collision(this->rec.getGlobalBounds())){
		was_collision = true;
		return true;
	}
	return false;
}

void Bullet::moving(void){
	if (!was_collision){
		// std::cout<<"Bullet direction "<<dx<< ' '<<dy<<std::endl;
		rec.move(dx, dy);
	}
}

void Bullet::draw(sf::RenderWindow& window){
	if (!was_collision)
		window.draw(rec);
	
}