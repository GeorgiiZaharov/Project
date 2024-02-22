#include "GameEngine.hpp"

GameEngine::GameEngine(int screen_w, int screen_h)
: window(sf::VideoMode(screen_w, screen_h), "The best game"){
	window.setFramerateLimit(60);
	b = Board(screen_w, screen_h, 10, 15);
	p = Hero(10.f, 10.f, HERO_WIDTH, HERO_HEIGHT);
    e = Enemy(b, 690.f, 490.f, ENEMY_WIDTH, ENEMY_HEIGHT);
}

void GameEngine::run(void){
	b.dfs(0, 0);
    
	while (window.isOpen()){
		input();
		draw();
	}
}

void GameEngine::draw(void){
	window.clear();
	b.draw(window);
	p.draw(window);
    e.draw(window);
	window.display();
}

void GameEngine::input(void) {
    p.dx = 0;
    p.dy = 0;
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                isMovingUp = true;

            if (event.key.code == sf::Keyboard::Right)
                isMovingRight = true;

            if (event.key.code == sf::Keyboard::Down)
                isMovingDown = true;

            if (event.key.code == sf::Keyboard::Left)
                isMovingLeft = true;
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Up)
                isMovingUp = false;
            if (event.key.code == sf::Keyboard::Right)
                isMovingRight = false;
            if (event.key.code == sf::Keyboard::Down)
                isMovingDown = false;
            if (event.key.code == sf::Keyboard::Left)
                isMovingLeft = false;
        }
    }

    if (isMovingUp){
        p.dy -= 1;
        p.rec.setRotation(90.f);
    }
    if (isMovingRight){
        p.dx += 1;
        p.rec.setRotation(0);
    }
    if (isMovingDown){
        p.dy += 1;
        p.rec.setRotation(270.f);
    }
    if (isMovingLeft){
        p.dx -= 1;
        p.rec.setRotation(180.f);
    }

    p.moving(b);
    e.moving(b, p);
}