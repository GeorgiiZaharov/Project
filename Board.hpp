#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

#include "Cell.hpp"

class Board
{
public:
	Board(int w, int h, int n, int m);
	// ширина высота количество_столбцов_ячеек количество_строк_ячеек начало_отсчета_по_х начало_отсчета_по_y
	~Board();

///////////////////////////////////////////////////////////////////////////////////////	
	std::set<std::pair<int, int>> was;
	int get_cor_arr(int w, int h);
	bool is_go_abroad(int w, int h);
	void dfs(int w, int h);
///////////////////////////////////////////////////////////////////////////////////////	

	void draw(sf::RenderWindow& window);
	bool check_collision(sf::FloatRect r);

	Cell* cells = nullptr;
private:
	int n, m;
};

#endif