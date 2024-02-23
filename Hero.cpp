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

	gun = Gun(30, 10.f, 6, 2000.f);

	alive = true;

}

Hero& Hero::operator=(const Hero& h){
	this->rec = h.rec;
	this->dx = h.dx;
	this->dy = h.dy;
	this->speed = h.speed;
	this->gun = h.gun;
	return *this;
}

void Hero::draw(sf::RenderWindow& window){
	gun.draw(window);
	window.draw(rec);
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

void Hero::shooting(float dx, float dy, float cur_time){
	sf::FloatRect coordinates = this->rec.getGlobalBounds();
	float x = coordinates.left + coordinates.width/2;
	float y = coordinates.top + coordinates.height/2;
	gun.shoot(x, y, dx, dy, cur_time);
}
