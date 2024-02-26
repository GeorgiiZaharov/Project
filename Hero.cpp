#include "Hero.hpp"

Hero::Hero(sf::Texture &tex, float x, float y, float w, float h){
	this->tex = &tex;
	this->rec.setTexture(*this->tex);//загружаем sprite

	//масштабируем
	sf::FloatRect imageBounds = this->rec.getGlobalBounds();
	float imageScale_x = w / imageBounds.width;
	float imageScale_y = h / imageBounds.height;
	this->rec.setScale(imageScale_x, imageScale_y);

	//выбираем часть изображения со спрайтом
	this->rec.setTextureRect(sf::IntRect(0,0,64, 64));

	//устанавливаем напраление
	dx = 1;
	dy = 0;

	//скорсть
	speed = HERO_SPEED;

	//индекс клетки лабиринта
	poz_x = 0;
	poz_y = 0;

	//перемещаем точку в центр спрайта
	this->rec.setOrigin(rec.getLocalBounds().width / 2.f, rec.getLocalBounds().height / 2.f);
	this->rec.setPosition(x + w/2, y + h/2); // устанавливаем позицию

	// //инициализируем оружие
	// //количество_патронов один_выстрел_раз_в_200мс скорость_пули время_перезарядки_мс
	// gun = Gun(30, 200.f, 6, 2000.f);

	//живой
	alive = true;
}

Hero& Hero::operator=(const Hero& h){
	this->gun = h.gun;
	this->alive = h.alive;
	this->poz_x = h.poz_x;
	this->poz_y = h.poz_y;
	this->dx = h.dx;
	this->dy = h.dy;
	this->speed = h.speed;
	this->rec = h.rec;
	this->tex = h.tex;

	//выбираем часть изображения со спрайтом
	// this->rec.setTextureRect(sf::IntRect(0,0,64, 64));

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
    rotate(dx, dy);
	gun.shoot(x, y, dx, dy, cur_time);
}
