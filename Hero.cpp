#include "Hero.hpp"

Hero::Hero(float x, float y, float w, float h){
	this->rec = sf::RectangleShape(sf::Vector2f(w, h));
	this->rec.setPosition(x, y);
	this->rec.setFillColor(sf::Color::White);


	rec.setOrigin(w/2, h/2);
	rec.move(w/2, h/2);


	dx = 0;
	dy = 0;
	speed = HERO_SPEED;

	poz_x = 0;
	poz_y = 0;
}

Hero& Hero::operator=(const Hero& h){
	this->rec = h.rec;
	this->dx = h.dx;
	this->dy = h.dy;
	this->speed = h.speed;
	return *this;
}


void Hero::moving(Board& b){
	for (int i = 0; i < speed; ++i){
		rec.move(dx, dy);
		if (b.check_collision(rec.getGlobalBounds())){
			rec.move(-dx, -dy);
			break;
		}
	}
	sf::FloatRect coordinates = rec.getGlobalBounds();
	poz_x = (int)((coordinates.left + coordinates.width/2)/b.cell_w);
	poz_y = (int)((coordinates.top + coordinates.height/2)/b.cell_h);
}