#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
	void draw(sf::RenderWindow& window);
	sf::RectangleShape rec;
};

#endif