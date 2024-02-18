#include "Cell.hpp"

Cell::Cell(){}
Cell::Cell(float x, float y, float cell_w, float cell_h, float border_width){
	rec = sf::RectangleShape(sf::Vector2f(cell_w, cell_h));
	rec.setPosition(x, y);
	rec.setFillColor(sf::Color::Red);

	line_up = sf::RectangleShape(sf::Vector2f(cell_w, border_width));
	line_up.setPosition(x, y);
	line_up.setFillColor(sf::Color::Green);

	line_right = sf::RectangleShape(sf::Vector2f(border_width, cell_h));
	line_right.setPosition(x + cell_w - border_width, y);
	line_right.setFillColor(sf::Color::Green);

	line_down = sf::RectangleShape(sf::Vector2f(cell_w, border_width));
	line_down.setPosition(x, y + cell_h - border_width);
	line_down.setFillColor(sf::Color::Green);

	line_left = sf::RectangleShape(sf::Vector2f(border_width, cell_h));
	line_left.setPosition(x, y);
	line_left.setFillColor(sf::Color::Green);
}

Cell& Cell::operator=(const Cell& c){
	this->rec = c.rec;
	this->line_up = c.line_up;
	this->line_right = c.line_right;
	this->line_down = c.line_down;
	this->line_left = c.line_left;
	this->x = c.x;
	this->y = c.y;
	return *this;
}

void Cell::draw(sf::RenderWindow& window){
	window.draw(rec);
	if (is_up) window.draw(line_up);
	if (is_right) window.draw(line_right);
	if (is_down) window.draw(line_down);
	if (is_left) window.draw(line_left);
}

bool Cell::check_collision(sf::FloatRect r){
	if (is_up && line_up.getGlobalBounds().intersects(r)){
		return true;
	}
	if (is_right && line_right.getGlobalBounds().intersects(r)){
		return true;
	}
	if (is_down && line_down.getGlobalBounds().intersects(r)){
		return true;
	}
	if (is_left && line_left.getGlobalBounds().intersects(r)){
		return true;
	}
	return false;
}