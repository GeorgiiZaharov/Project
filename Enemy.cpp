#include "Enemy.hpp"

Enemy::Enemy(sf::Texture& tex, Board& b ,float x, float y, float w, float h){
	this->tex = &tex;

	this->rec.setTexture(*this->tex);//загружаем sprite

	//выбираем часть изображения со спрайтом
	this->rec.setTextureRect(sf::IntRect(0,0,64, 64));

	//масштабируем
	sf::FloatRect imageBounds = this->rec.getGlobalBounds();
	float imageScale_x = w / imageBounds.width;
	float imageScale_y = h / imageBounds.height;
	this->rec.setScale(imageScale_x, imageScale_y);

	//устанавливаем начальное положение
	rec.setPosition(x, y);

	//устанавливаем напраление
	dx = 0;
	dy = 0;

	//скорсть
	speed = ENEMY_SPEED;

	//вычисляем текущуюю позицию на поле
	sf::FloatRect coordinates = rec.getGlobalBounds();
	poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);

	//флаг жизни и присутствия игрока
	saw_the_player = false;
	alive = true;

	//дальность видимости
	distance = 4;

	//перемещаем точку в центр спрайта
	this->rec.setOrigin(rec.getLocalBounds().width / 2.f, rec.getLocalBounds().height / 2.f);
	this->rec.setPosition(x + w / 2, y + h / 2); // устанавливаем позицию

	// //инициализируем оружие
	// //количество_патронов один_выстрел_раз_в_200мс скорость_пули время_перезарядки_мс
	// gun = Gun(10, 500.f, 3, 2000.f);
}
	
Enemy& Enemy::operator=(const Enemy& e){
	this->path_to_player = e.path_to_player;
	this->distance = e.distance;
	this->damage = e.damage;
	this->saw_the_player = e.saw_the_player;
	this->alive = e.alive;
	this->gun = e.gun;
	this->rec = e.rec;
	this->tex = e.tex;
	this->poz_x = e.poz_x;
	this->poz_y = e.poz_y;
	this->dx = e.dx;
	this->dy = e.dy;
	this->speed = e.speed;

	//выбираем часть изображения со спрайтом
	// this->rec.setTextureRect(sf::IntRect(0,0,64, 64));

	return *this;
}

void Enemy::moving(Board& b, Hero& p){
	if (alive){
		for (int i = 0; i < speed; ++i){
			path_to_player.clear();
			bfs(b, p);
			if (static_cast<int>(path_to_player.size()) == 0){
				saw_the_player = true;
				
				sf::FloatRect coordinates_player = p.rec.getGlobalBounds();
				sf::FloatRect coordinates_enemy = this->rec.getGlobalBounds();


				dx = coordinates_player.left - coordinates_enemy.left;
				dy = coordinates_player.top - coordinates_enemy.top;

				float len_direct = static_cast<float>(std::sqrt(dx * dx + dy * dy)) + 0.000000001f;

				dx = dx/len_direct;
				dy = dy/len_direct;
			}

			else if (static_cast<int>(path_to_player.size()) <= distance || saw_the_player){
				saw_the_player = true;
				sf::FloatRect coordinates = rec.getGlobalBounds();

				if (dy == -1){			//up
					poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
					poz_y = static_cast<int>((coordinates.top + coordinates.height/2 + 1.f/4 * b.cell_h)/b.cell_h);
				}			
				else if (dx == 1){		//right
					poz_x = static_cast<int>((coordinates.left + coordinates.width/2 - 1.f/4 * b.cell_w)/b.cell_w);
					poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);
				}
				else if (dy == 1){		//down
					poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
					poz_y = static_cast<int>((coordinates.top + coordinates.height/2 - 1.f/4 * b.cell_h)/b.cell_h);
				}
				else if (dx == -1){		//left
					poz_x = static_cast<int>((coordinates.left + coordinates.width/2 + 1.f/4 * b.cell_w)/b.cell_w);
					poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);
				}

				std::pair<int, int> target = path_to_player[0];
				dx = target.first - poz_x;
				dy = target.second - poz_y;
			}
			rec.move(dx, dy);
		}
		rotate(dx, dy);
	}

	for (int i = 0; i < gun.magazine_size - gun.bullets_in_gun; ++i){
		for (int j = 0; j < gun.speed_bullet; ++j){
			gun.magazine[i].moving();
			if (!gun.magazine[i].was_collision){
				if (gun.magazine[i].check_collision(p.rec.getGlobalBounds())){
					p.alive = false;
					std::cout<<"KILL"<<std::endl;
				}
				gun.magazine[i].check_collision(b);
			}
		}
	}

}

bool Enemy::is_open_pozition(Board& b){
	if (path_to_player.size() == 0)return true;

	sf::FloatRect coordinates = rec.getGlobalBounds();
	int cur_poz_enemy_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	int cur_poz_enemy_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);

	bool flag = true;
	for (auto i : this->path_to_player){
		if (i.first != cur_poz_enemy_x){
			flag = false;
			break;
		}
	}
	if (flag)return true;

	flag = true;
	for (auto i : this->path_to_player){
		if (i.second != cur_poz_enemy_y){
			flag = false;
			break;
		}
	}
	if (flag)return true;

	return false;
}

void Enemy::shooting(Board& b, Hero& p, float cur_time){
	if (alive && is_open_pozition(b)){
		sf::FloatRect coordinates = this->rec.getGlobalBounds();
		float x = coordinates.left + coordinates.width/2;
		float y = coordinates.top + coordinates.height/2;

		sf::FloatRect target_coordinates = p.rec.getGlobalBounds();
		float target_x = target_coordinates.left + target_coordinates.width/2;
		float target_y = target_coordinates.top + target_coordinates.height/2;

		int result = gun.shoot(x, y, target_x - x, target_y - y, cur_time);
		if (result == 1){
			// std::cout<<this<<" BAH"<<std::endl;
		}
		if (result == 0){
			// std::cout<<this<<" RECHARGE"<<std::endl;
		}
	}
}

void Enemy::bfs(Board& b, Hero& p){
	bool flag = false;
	std::pair<int, int> from;
	std::map<std::pair<int, int>, std::pair<int, int>> was;
	was[std::make_pair(poz_x, poz_y)] = std::make_pair(-1, -1);
	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair(poz_x, poz_y));

	// for (auto i : b.graph){
	// 	std::cout<<i.first.first << ' '<<i.first.second<<'\n';
	// 	std::cout<<"[";
	// 	for (auto j : b.graph[i.first]){
	// 		std::cout<<j.first<<" : "<<j.second<<std::endl;
	// 	}
	// 	std::cout<<"]"<<std::endl;
	// }

	while (!q.empty()){

		from = q.front();			//получаем вершину с которой будем работать
		q.pop();
		for (std::pair<int, int> i : b.graph[from]){	 //смотрим все варианты куда можем идти
			if (!was.count(i)){		//здесь еще не были
				was[i] = from;		//запоминаем откуда мы сюда попали
				q.push(i);			//добавляем в очередь
			}
			if (i == std::make_pair(p.poz_x, p. poz_y)){
				flag = true;			//если нашли то прекращаем поиск
				break;
			}
		}
		if (flag) break;
	}

	//собираем путь от позиции player до позиции enemy)
	std::pair<int, int> cur = std::make_pair(p.poz_x, p. poz_y);
	while (cur != std::make_pair(-1, -1)){
		path_to_player.push_back(cur);
		cur = was[cur];
	}

	//разворачиваем получившийся путь
	reverse(std::begin(path_to_player), std::end(path_to_player));
	path_to_player.erase(std::begin(path_to_player));			//последний ход будем делать исходя из координат player
}

void Enemy::draw(sf::RenderWindow& window){
	if (alive)	window.draw(rec);
	gun.draw(window);//ашалеть
}