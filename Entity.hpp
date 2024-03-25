#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "includes.hpp"

class Entity
{
public:
	// виртуальная функция отрисовки объекта
	virtual void draw(sf::RenderWindow& window) = 0;
	// функция разворота спрайта в заданном направлении
	void rotate(float dx, float dy);
	// спрайт и текстура объекта
	sf::Sprite rec;
	sf::Texture* tex;
	// текущее положение в пространстве объекта
	int poz_x, poz_y;
	// направлние взгляда объекта
	float dx, dy;
	// скорость объекта
	int speed;
	// параметры хдоровья объекта
	int health, max_health;
};

#endif