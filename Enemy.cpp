#include "Enemy.hpp"

Enemy::Enemy(const Board&b ,float x, float y, float w, float h){
	this->rec = sf::RectangleShape(sf::Vector2f(w, h));
	this->rec.setPosition(x, y);
	this->rec.setFillColor(sf::Color::Black);

	dx = 0;
	dy = 0;
	speed = ENEMY_SPEED;
	distance = 15;


	sf::FloatRect coordinates = rec.getGlobalBounds();
	poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);
}
	
Enemy& Enemy::operator=(const Enemy& e){
	this->rec = e.rec;
	this->dx = e.dx;
	this->dy = e.dy;
	this->speed = e.speed;

	this->poz_x = e.poz_x;
	this->poz_y = e.poz_y;

	this->distance = e.distance;
	this->damage = e.damage;
	this->path_to_player = e.path_to_player;

	return *this;
}

void Enemy::moving(Board& b, Hero& p){

	// bfs(b, p);
	// std::cout<<"path_to_player\n:";
	// for (auto i : path_to_player){
	// 	std::cout<<i.first<<", "<<i.second<<std::endl;
	// }
	// if (static_cast<int>(path_to_player.size()) == 1){
	// 	std::cout<<"Path equal ZERO\n";
	// 	for (int i = 0; i < speed; ++i){
	// 		sf::FloatRect coordinates_player = p.rec.getGlobalBounds();
	// 		sf::FloatRect coordinates_enemy = this->rec.getGlobalBounds();


	// 		dx = coordinates_player.left - coordinates_enemy.left;
	// 		dy = coordinates_player.top - coordinates_enemy.top;
	// 		std::cout<<"player coordinates "<<coordinates_player.left<< ' '<<coordinates_player.top<<std::endl;
	// 		std::cout<<"enemy coordinates "<<coordinates_enemy.left<< ' '<<coordinates_enemy.top<<std::endl;

	// 		float len_direct = static_cast<float>(std::sqrt(dx * dx + dy * dy));
	// 		std::cout<<"len "<<len_direct<<std::endl;
	// 		dx = dx/len_direct;
	// 		dy = dy/len_direct;
	// 		std::cout<<"coordinate "<<dx<<" "<<dy<<std::endl;
	// 		rec.move(dx, dy);

	// 		if (std::abs(dx) >= std::abs(dy)){
	// 			if (dx < 0) dx = -1;
	// 			else dx = 1;
	// 			dy = 0;
	// 		}
	// 		else{
	// 			if (dy < 0) dy = -1;
	// 			else dy = 1;
	// 			dx = 0;
	// 		}

	// 	}
	// }

	// else if (static_cast<int>(path_to_player.size()) <= distance){
	// 	sf::FloatRect coordinates = rec.getGlobalBounds();
	// 	// poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	// 	// poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);

	// 	if (dy == -1){			//up
	// 		poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	// 		poz_y = static_cast<int>((coordinates.top + coordinates.height/2 + 1.f/4 * b.cell_h)/b.cell_h);
	// 	}			
	// 	else if (dx == 1){		//right
	// 		poz_x = static_cast<int>((coordinates.left + coordinates.width/2 - 1.f/4 * b.cell_w)/b.cell_w);
	// 		poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);
	// 	}
	// 	else if (dy == 1){		//down
	// 		poz_x = static_cast<int>((coordinates.left + coordinates.width/2)/b.cell_w);
	// 		poz_y = static_cast<int>((coordinates.top + coordinates.height/2 - 1.f/4 * b.cell_h)/b.cell_h);
	// 	}
	// 	else if (dx == -1){					//left
	// 		poz_x = static_cast<int>((coordinates.left + coordinates.width/2 + 1.f/4 * b.cell_w)/b.cell_w);
	// 		poz_y = static_cast<int>((coordinates.top + coordinates.height/2)/b.cell_h);
	// 	}


	// 	std::pair<int, int> target = path_to_player[0];
	// 	dx = target.first - poz_x;
	// 	dy = target.second - poz_y;
	// 	for (int i = 0; i < speed; ++i){
	// 		rec.move(dx, dy);
	// 	}
	// }
	// path_to_player.clear();



	for (int i = 0; i < speed; ++i){
		path_to_player.clear();
		bfs(b, p);
		// std::cout<<"path_to_player\n:";
		// for (auto i : path_to_player){
		// 	std::cout<<i.first<<", "<<i.second<<std::endl;
		// }
		if (static_cast<int>(path_to_player.size()) == 0){
			// std::cout<<"Path equal ZERO\n";
			sf::FloatRect coordinates_player = p.rec.getGlobalBounds();
			sf::FloatRect coordinates_enemy = this->rec.getGlobalBounds();


			dx = coordinates_player.left - coordinates_enemy.left;
			dy = coordinates_player.top - coordinates_enemy.top;
			// std::cout<<"player coordinates "<<coordinates_player.left<< ' '<<coordinates_player.top<<std::endl;
			// std::cout<<"enemy coordinates "<<coordinates_enemy.left<< ' '<<coordinates_enemy.top<<std::endl;

			float len_direct = static_cast<float>(std::sqrt(dx * dx + dy * dy)) + 0.000000001f;

			// std::cout<<"len "<<len_direct<<std::endl;
			dx = dx/len_direct;
			dy = dy/len_direct;
			// std::cout<<"coordinate "<<dx<<" "<<dy<<std::endl;


		}

		else if (static_cast<int>(path_to_player.size()) <= distance){
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

