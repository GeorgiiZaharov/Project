#ifndef CELL_HPP
#define CELL_HPP
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell();
	Cell(float x, float y, float cell_w, float cell_h, float border_width);

	Cell& operator=(const Cell& c);
	
	void draw(sf::RenderWindow& window);
	bool check_collision(sf::FloatRect r);

	sf::RectangleShape rec, line_up, line_right, line_down, line_left;

	float x, y;
	bool is_up = true, is_right = true, is_down = true, is_left = true;
};

#endif