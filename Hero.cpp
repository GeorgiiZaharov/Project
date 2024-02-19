#include "Hero.hpp"

Hero::Hero(){}

Hero::Hero(float x, float y, float w, float h){
	this->rec = sf::RectangleShape(sf::Vector2f(w, h));
	this->rec.setPosition(x, y);
	this->rec.setFillColor(sf::Color::White);

	vx = 0.f;
	vy = 0.f;
	speed = HERO_SPEED;
}

Hero& Hero::operator=(const Hero& h){
	this->rec = h.rec;
	this->vx = h.vx;
	this->vy = h.vy;
	this->speed = h.speed;
	return *this;
}


void Hero::moving(Board& b, int w, int h){
	// rec.move(w * speed, h * speed);
	// if (b.check_collision(rec.getGlobalBounds())){
	// 	rec.move(-w * speed, -h * speed);
	// }
	for (int i = 0; i < speed; ++i){
		rec.move(w, h);
		if (b.check_collision(rec.getGlobalBounds())){
			rec.move(-w, -h);
			break;
		}

	}
}