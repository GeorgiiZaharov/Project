#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "Settings.hpp"
#include "Cell.hpp"

class Board
{
public:
	Board(void){};
	Board(int screen_w, int screen_h, int n, int m);
	// ширина высота количество_столбцов_ячеек количество_строк_ячеек начало_отсчета_по_х начало_отсчета_по_y
	~Board();

	Board& operator=(const Board& b);

///////////////////////////////////////////////////////////////////////////////////////	
	std::set<std::pair<int, int>> was;
	int get_cor_arr(int w, int h);
	bool is_go_abroad(int w, int h);
	void dfs(int w, int h);
///////////////////////////////////////////////////////////////////////////////////////	

	void draw(sf::RenderWindow& window);
	bool check_collision(sf::FloatRect r);

	std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> graph;
	Cell* cells = nullptr;
	float cell_w, cell_h;
private:
	int n, m, screen_w, screen_h;
};

#endif