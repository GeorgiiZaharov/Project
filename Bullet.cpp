#include "Bullet.hpp"

Bullet::Bullet(){
	was_collision = false;
}

Bullet::Bullet(sf::Texture& tex, float w, float h, float x, float y, float dx, float dy, int speed){

	float len_direct = static_cast<float>(std::sqrt(dx * dx + dy * dy));
	this->dx = dx / len_direct;
	this->dy = dy / len_direct;

	this->rec.setTexture(tex);
	this->rec.setPosition(x, y);
	sf::FloatRect imageBounds = this->rec.getGlobalBounds();
	float imageScale_x = w / imageBounds.width;
	float imageScale_y = h / imageBounds.height;
	this->rec.setScale(imageScale_x, imageScale_y);


	// rotate
	this->rec.setOrigin(w/2, h/2);
	this->rec.setPosition(x + w/2, y + h/2);
	this->rec.rotate(std::atan2(dy, dx) * 180.f / 3.1415926535f); /////////////////////////////////////////


	this->speed = speed;

	this->was_collision = false;
}



Bullet& Bullet::operator=(const Bullet& b){
	this->was_collision = b.was_collision;
	this->rec = b.rec;
	this->poz_x = b.poz_x;
	this->poz_y = b.poz_y;
	this->dx = b.dx;
	this->dy = b.dy;
	this->speed = b.speed;
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

void Bullet::moving(){
	if (!was_collision){
		// std::cout<<"Bullet direction "<<dx<< ' '<<dy<<std::endl;
		rec.move(dx, dy);
	}
}

void Bullet::draw(sf::RenderWindow& window){
	if (!was_collision)
		window.draw(rec);
	
}