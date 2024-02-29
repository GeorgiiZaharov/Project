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
	GameEngine(void);
	~GameEngine();
	
	void run(void);
	void draw(void);
	void input(void);

	void restart(void);
private:
	Board b;
	Hero p;

	int screen_w, screen_h;
	int n, m; // количество ячеек ширины и высоты соотв.
	float human_size;
	int num_enemy;


	std::vector<Enemy> enemies;
	sf::RenderWindow window;

	sf::Clock clock;

	sf::Texture texHero, texEnemy, texBullet;

	sf::Font textFont;
	sf::Text levelText, nbulletsText, healthText, gunStatusText,
		nenemyText, moneyText;

	sf::RectangleShape infPanel;

	///////////////////////////
	bool isMovingUp = false, isMovingDown = false, isMovingLeft = false, isMovingRight = false;
	bool isShootingUp = false, isShootingDown = false, isShootingLeft = false, isShootingRight = false;
	///////////////////////////
	int enemies_alive;
	int cur_level;
	int nbullets_in_player_gun, player_health, player_speed, player_damage;
	int nbullets_in_enemy_gun, enemy_health, enemy_speed, enemy_damage;

	sf::RectangleShape healthButton, damageButton, bulletButton;
	sf::Text healthWord, damageWord, bulletWord;


	int money_count;
};

#endif