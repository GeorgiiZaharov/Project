#include "Hero.hpp"

/*
	Конструктор класса Hero
		&tex - ссылка на текстуру изображения
		x, y - положение игрока в пикселях от левого верхнего угла экрана
		w, h - высота и ширина спрайта персонажа
		health - максимальное здоровье персонажа
		speed - скорость персонажа
		damage - урон наносимый врагам персонажем
*/
Hero::Hero(sf::Texture &tex, float x, float y, float w, float h, int health, int speed, int damage){
	// сохраняем ссылку на текстуру Hero
	this->tex = &tex;
	// загружаем sprite
	this->rec.setTexture(*this->tex);

	//масштабируем спрайт персонажа
	sf::FloatRect imageBounds = this->rec.getGlobalBounds();
	float imageScale_x = w / imageBounds.width;
	float imageScale_y = h / imageBounds.height;
	this->rec.setScale(imageScale_x, imageScale_y);

	// инициализируем параметры отвечающие за здоровье персонажа
	this->max_health = health;
	this->health = max_health;

	// инициализируем полосу здоровья
	borderHealth.setFillColor(sf::Color::Transparent);
	borderHealth.setOutlineThickness(-1.f);
	borderHealth.setOutlineColor(sf::Color::Black);
	borderHealth.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));

	healthBar.setPosition(sf::Vector2f(x, y - BAR_HEIGHT));

	// устанавливаем значение урона персонажа
	this->damage = damage;

	// устанавливаем напраление взгляда персонажа (вправо)
	dx = 1;
	dy = 0;

	//устанавливаем параметр отвечающий за скорость персонажа
	this->speed = speed;

	//индекс клетки лабиринта
	poz_x = 0;
	poz_y = 0;

	//перемещаем точку относительно которой будет разворот в центр спрайта
	this->rec.setOrigin(rec.getLocalBounds().width / 2.f, rec.getLocalBounds().height / 2.f);
	this->rec.setPosition(x + w/2, y + h/2); // устанавливаем позицию
}

/* 
	Конструктор копирования класса Hero
		h - объект класса Hero от которого нужно унаследоваться
*/
Hero& Hero::operator=(const Hero& h){
	// копируем поля объекта h в атрибуты текущего класса
	this->gun = h.gun;
	this->poz_x = h.poz_x;
	this->poz_y = h.poz_y;
	this->dx = h.dx;
	this->dy = h.dy;
	this->speed = h.speed;
	this->rec = h.rec;
	this->tex = h.tex;

	this->max_health = h.max_health;
	this->health = h.health;
	this->damage = h.damage;

	this->borderHealth = h.borderHealth;
	this->healthBar = h.healthBar;

	return *this;
}

/*
	Функция отрисовки персонажа
		window - окно куда будем изображатть персонажа
*/
void Hero::draw(sf::RenderWindow& window){
	// получение текущич координат персонажа
	sf::FloatRect player_cor = rec.getGlobalBounds();
	// расчет процента здоровья персонажа
	float attitude = static_cast<float>(health) / max_health;

	// в зависимости от процента здоровья подкршиваем полосу здоровья
	if (attitude >= 0.75)healthBar.setFillColor(sf::Color::Green);
	else if (attitude >= 0.5)healthBar.setFillColor(sf::Color::Yellow);
	else healthBar.setFillColor(sf::Color::Red);

	// устанавливаем положение полосы здоровья относительно персонажа
	healthBar.setPosition(player_cor.left, player_cor.top - BAR_HEIGHT);
	healthBar.setSize(sf::Vector2f(attitude * BAR_WIDTH, BAR_HEIGHT));
	borderHealth.setPosition(player_cor.left, player_cor.top - BAR_HEIGHT);

	// отрисовка оружия и патронов персонажа
	gun.draw(window);
	// отрисовываем элеметы полосы здоровья персонажа
	window.draw(healthBar);
	window.draw(borderHealth);
	// отрисовываем сам спрайт персонажа
	window.draw(rec);
}

/*
	Функция перемещения персонажа
		b - экземпляр класса Board
*/
void Hero::moving(Board& b){
	// цикл для задания скорости персонажа и контроля столкновений
	for (int i = 0; i < speed; ++i){
		// пробуем переместить персонажа в заданном направлении
		rec.move(dx, dy);
		// если случилась коллизия
		if (b.check_collision(rec.getGlobalBounds())){
			// перемещаемся назад
			rec.move(-dx, -dy);
			break;
		}
	}
	// после перемещения обновляем координаты
	sf::FloatRect coordinates = rec.getGlobalBounds();
	poz_x = (int)((coordinates.left + coordinates.width/2)/b.cell_w);
	poz_y = (int)((coordinates.top + coordinates.height/2)/b.cell_h);
}

/*
	Функция стрельбы персонажа
		dx, dy - направление стрельбы
		shootSound - звук выстрела
		rechargeSound - звук перезарядки
		cur_time - время попытки текущего выстрела	
*/
void Hero::shooting(float dx, float dy, sf::Sound& shootSound, sf::Sound& rechargeSound, float cur_time){
	// расчитываем текущее положение персонажа
	sf::FloatRect coordinates = this->rec.getGlobalBounds();
	float x = coordinates.left + coordinates.width/2;
	float y = coordinates.top + coordinates.height/2;
	// разворачиваем спрайт персонажа в сторону стрельбы
    this->rotate(dx, dy);
    // пробуем стрелять
	int result = this->gun.shoot(x, y, dx, dy, cur_time);
	// если в result 1 то произошол выстрел
	// если в result 0 то перезарядка
	if (result == 1){
		// прогирываем звук выстрела
		shootSound.play();
		// говорим что стрельбы была => перезарядки небыло
		wasRechargeSound = false;
	}
	// если до этого мы не проигрывали звук перезарядки
	if (result == 0 && !wasRechargeSound){
		// проигрываем его
		rechargeSound.play();
		// говорим что уже проигрывали
		wasRechargeSound = true;
	}
}
