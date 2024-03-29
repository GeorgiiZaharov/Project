#include "Board.hpp"

Board::Board(int screen_w, int screen_h, int n, int m){
	this->n = n;		//ширина поля в клетках
	this->m = m;		//высота поля в клетках

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	this->cell_w = screen_w / (float)n;
	this->cell_h = screen_h / (float)m;

	this->border_width = BORDER_WIDTH;

	cells.resize(n * m);
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			cells[get_cor_arr(j, i)] = Cell(j * cell_w, i * cell_h, cell_w, cell_h, border_width);
		}
	}
}

Board::~Board(){
	cells.clear();
	graph.clear();
	was.clear();
}

Board& Board::operator=(const Board& b){
	this->graph = b.graph;
	this->cells = b.cells;
	this->cell_w = b.cell_w;
	this->cell_h = b.cell_h;
	this->border_width = b.border_width;
	this->n = b.n;
	this->m = b.m;
	this->screen_w = b.screen_w;
	this->screen_h = b.screen_h;
	return *this;
}

int Board::get_cor_arr(int w, int h){
	return h * n + w;
}

bool Board::is_go_abroad(int w, int h){
	if (w < 0 || h < 0 || w >= n || h >= m) return true;
	return false;
}

void Board::dfs(int w, int h){
	was.insert(std::make_pair(w, h));		// отметились что побывали
	while (1){
		std::vector<std::pair<int, int>> v;			// находим все варианты куда можем
		if (!is_go_abroad(w, h + 1) && !was.count(std::make_pair(w, h + 1))) v.push_back(std::make_pair(0, 1));
		if (!is_go_abroad(w + 1, h) && !was.count(std::make_pair(w + 1, h))) v.push_back(std::make_pair(1, 0));
		if (!is_go_abroad(w, h - 1) && !was.count(std::make_pair(w, h - 1))) v.push_back(std::make_pair(0, -1));
		if (!is_go_abroad(w - 1, h) && !was.count(std::make_pair(w - 1, h))) v.push_back(std::make_pair(-1, 0));

		if (v.size() == 0) break;		//были везде в округе

		int choice = random() % v.size();		// выбираем куда идти
		int delta_w = v[choice].first, delta_h = v[choice].second;		// запоминаем направление

		this->graph[std::make_pair(w, h)].push_back(std::make_pair(w + delta_w, h + delta_h));	// добавляем вершины в граф
		this->graph[std::make_pair(w + delta_w, h + delta_h)].push_back(std::make_pair(w, h));	// добавляем вершины в граф

		// в зависимости от направления удаляем стенки следующего и текущего
		if (delta_h == 1){
			cells[get_cor_arr(w + delta_w, h + delta_h)].is_up = false;
			cells[get_cor_arr(w, h)].is_down = false;
		}
		else if (delta_w == 1){
			cells[get_cor_arr(w + delta_w, h + delta_h)].is_left = false;
			cells[get_cor_arr(w, h)].is_right = false;
		}
		else if (delta_h == -1){
			cells[get_cor_arr(w + delta_w, h + delta_h)].is_down = false;
			cells[get_cor_arr(w, h)].is_up = false;
		}
		else if (delta_w == -1){
			cells[get_cor_arr(w + delta_w, h + delta_h)].is_right = false;
			cells[get_cor_arr(w, h)].is_left = false;
		}
		v.clear();
		dfs(w + delta_w, h + delta_h);
	}
}

void Board::draw(sf::RenderWindow& window){
	for (int i = 0; i < n * m; ++i){
		cells[i].draw(window);
	}
}

bool Board::check_collision(sf::FloatRect r){
	for (int i = 0; i < n * m; ++i){
		if (cells[i].check_collision(r)) return true;
	}
	return false;
}