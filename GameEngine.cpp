#include "GameEngine.hpp"

GameEngine::GameEngine(int screen_w, int screen_h)
: window(sf::VideoMode(screen_w, screen_h), "The best game"){
    sf::Image icon;
    if (!icon.loadFromFile("src/icon.png")){
        std::cerr << "No such file with icon" << std::endl;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
	window.setFramerateLimit(60);
	b = Board(screen_w, screen_h, 10, 15);
	p = Hero(10.f, 10.f, HERO_WIDTH, HERO_HEIGHT);

    enemies.clear();
    float rand_cor_x;
    float rand_cor_y;
    for (int i = 0; i < ENEMY_COUNT; ++i){
        rand_cor_x = (rand() % b.n) * b.cell_w + b.cell_w / 2 - ENEMY_WIDTH / 2;
        rand_cor_y = (rand() % b.m) * b.cell_h + b.cell_h / 2 - ENEMY_HEIGHT / 2;
        enemies.push_back(Enemy(b, rand_cor_x, rand_cor_y, ENEMY_WIDTH, ENEMY_HEIGHT));
    }

    clock.restart();
}

GameEngine::~GameEngine(){
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

    for (int i = 0; i < ENEMY_COUNT; ++i){
        enemies[i].draw(window);
    }

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
            //////////////////////////////////////////
            if (event.key.code == sf::Keyboard::W)
                // p.shooting(0, -1, clock.getElapsedTime().asMilliseconds());
                isShootingUp = true;
            if (event.key.code == sf::Keyboard::D)
                // p.shooting(1, 0, clock.getElapsedTime().asMilliseconds());
                isShootingRight = true;
            if (event.key.code == sf::Keyboard::S)
                // p.shooting(0, 1, clock.getElapsedTime().asMilliseconds());
                isShootingDown = true;
            if (event.key.code == sf::Keyboard::A)
                isShootingLeft = true;
                // p.shooting(-1, 0, clock.getElapsedTime().asMilliseconds());
            //////////////////////////////////////////


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
            //////////////////////////////////////////
            if (event.key.code == sf::Keyboard::W)
                isShootingUp = false;
            if (event.key.code == sf::Keyboard::D)
                isShootingRight = false;
            if (event.key.code == sf::Keyboard::S)
                // p.shooting(0, 1, clock.getElapsedTime().asMilliseconds());
                isShootingDown = false;
            if (event.key.code == sf::Keyboard::A)
                isShootingLeft = false;
                // p.shooting(-1, 0, clock.getElapsedTime().asMilliseconds());
            //////////////////////////////////////////

        }
    }

    if (isMovingUp){
        p.dy = -1;
        p.moving(b);
        p.dy = 0;
        p.rec.setRotation(90.f);
    }
    if (isMovingRight){
        p.dx = 1;
        p.moving(b);
        p.dx = 0;
        p.rec.setRotation(0);
    }
    if (isMovingDown){
        p.dy = 1;
        p.moving(b);
        p.dy = 0;
        p.rec.setRotation(270.f);
    }
    if (isMovingLeft){
        p.dx = -1;
        p.moving(b);
        p.dx = 1;
        p.rec.setRotation(180.f);
    }

    /////////////////////////////////
    if (isShootingUp) p.shooting(0, -1, clock.getElapsedTime().asMilliseconds());
    if (isShootingRight) p.shooting(1, 0, clock.getElapsedTime().asMilliseconds());
    if (isShootingDown) p.shooting(0, 1, clock.getElapsedTime().asMilliseconds());
    if (isShootingLeft) p.shooting(-1, 0, clock.getElapsedTime().asMilliseconds());
                



    for (auto& enemy : enemies){
        enemy.moving(b, p);
        enemy.shooting(b, p, clock.getElapsedTime().asMilliseconds());
    }

    for (int i = 0; i < p.gun.magazine_size - p.gun.bullets_in_gun; ++i){
        for (int j = 0; j < p.gun.speed_bullet; ++j){
            p.gun.magazine[i].moving();
            if (!p.gun.magazine[i].was_collision){
                for (auto& enemy : enemies){
                    if (p.gun.magazine[i].check_collision(enemy.rec.getGlobalBounds())){
                        enemy.alive = false;
                    }
                    p.gun.magazine[i].check_collision(b);
                }
            }
        }
    }

}