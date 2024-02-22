#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP 

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Board.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Settings.hpp"
	
class GameEngine
{
public:
	GameEngine(int screen_w, int screen_h);
	
	void run(void);

	void draw(void);
	void input(void);
private:
	Board b;
	Hero p;
	Enemy e;
	sf::RenderWindow window;

	///////////////////////////
	bool isMovingUp = false, isMovingDown = false, isMovingLeft = false, isMovingRight = false;
};

#endif