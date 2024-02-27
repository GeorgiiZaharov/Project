#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP 

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Board.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Settings.hpp"
	
class GameEngine
{
public:
	GameEngine(int screen_w, int screen_h);
	~GameEngine();
	
	void run(void);
	void draw(void);
	void input(void);

	void restart(void);
private:
	Board b;
	Hero p;

	int screen_w, screen_h;

	std::vector<Enemy> enemies;
	sf::RenderWindow window;

	sf::Clock clock;

	sf::Texture texHero, texEnemy, texBullet;
	sf::Font texFont;
	///////////////////////////
	bool isMovingUp = false, isMovingDown = false, isMovingLeft = false, isMovingRight = false;
	bool isShootingUp = false, isShootingDown = false, isShootingLeft = false, isShootingRight = false;
	///////////////////////////
	int enemies_alive;
};

#endif