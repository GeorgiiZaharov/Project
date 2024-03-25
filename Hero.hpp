#ifndef HERO_HPP
#define HERO_HPP

#include "includes.hpp"

#include "Entity.hpp"
#include "Board.hpp"
#include "Gun.hpp"
#include "Settings.hpp"
/*
	Класс Hero
		задает поведение главного героя
*/
class Hero : public Entity
{
public:
	// конструкторы класса Hero
	Hero(sf::Texture& tex, float x, float y, float w, float h, int health, int speed, int damage);
	Hero(void){};

	// конструктор копирования класса
	Hero& operator=(const Hero& h);

	// функция отрисовки объекта
	void draw(sf::RenderWindow& window) override;

	// функция перемещения объекта
	void moving(Board& b);

	// функция стрельбы
	void shooting(float dx, float dy, sf::Sound& shootSound, sf::Sound& rechargeSound, float cur_time);

	// текущий урон персонажа
	int damage; 

	// прямоугольники задающие полосу здоровья
	sf::RectangleShape borderHealth, healthBar;

	// экземпляр оружия для стрельбы
	Gun gun;

	// контроль повторения звука перезарядки
	bool wasRechargeSound = false; //нужно ли воспроизводить звук перезарядки
};

#endif