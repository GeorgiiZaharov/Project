#include "GameEngine.hpp"

GameEngine::GameEngine(int screen_w, int screen_h)
: window(sf::VideoMode(screen_w, screen_h), "The best game"){
    sf::Image icon;
    if (!icon.loadFromFile("src/icon.png")){
        std::cerr << "No such file with icon" << std::endl;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());

	window.setFramerateLimit(60);

	b = Board(screen_w, screen_h, 4, 3);

    if (!this->texHero.loadFromFile("hero.png"))std::cerr<<"No such file for hero";
	p = Hero(texHero, 10.f, 10.f, HERO_WIDTH, HERO_HEIGHT);
    p.gun = Gun(texBullet, 30, 200.f, 6, 2000.f);

    if (!this->texEnemy.loadFromFile("enemy.png"))std::cerr<<"No such file for enemy";
    if (!this->texBullet.loadFromFile("bullet.png"))std::cerr<<"No such file for bullet";


    enemies.clear();
    float rand_cor_x;
    float rand_cor_y;
    for (int i = 0; i < ENEMY_COUNT; ++i){
        rand_cor_x = (rand() % b.n) * b.cell_w + b.cell_w / 2 - ENEMY_WIDTH / 2;
        rand_cor_y = (rand() % b.m) * b.cell_h + b.cell_h / 2 - ENEMY_HEIGHT / 2;

        enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, ENEMY_WIDTH, ENEMY_HEIGHT);
        enemies[i].gun = Gun(texBullet, 10, 500.f, 3, 2000.f);

    }
    
    clock.restart();
}

GameEngine::~GameEngine(){
}

void GameEngine::run(void){
    std::cout<<"function run\n";
	b.dfs(0, 0);
    b.was.clear();
    std::cout<<"after bfs\n";
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
            if (event.key.code == sf::Keyboard::W)
                isMovingUp = true;

            if (event.key.code == sf::Keyboard::D)
                isMovingRight = true;

            if (event.key.code == sf::Keyboard::S)
                isMovingDown = true;

            if (event.key.code == sf::Keyboard::A)
                isMovingLeft = true;
            //////////////////////////////////////////
            if (event.key.code == sf::Keyboard::Up)
                isShootingUp = true;
            if (event.key.code == sf::Keyboard::Right)
                isShootingRight = true;
            if (event.key.code == sf::Keyboard::Down)
                isShootingDown = true;
            if (event.key.code == sf::Keyboard::Left)
                isShootingLeft = true;
            //////////////////////////////////////////
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W)
                isMovingUp = false;

            if (event.key.code == sf::Keyboard::D)
                isMovingRight = false;

            if (event.key.code == sf::Keyboard::S)
                isMovingDown = false;

            if (event.key.code == sf::Keyboard::A)
                isMovingLeft = false;
            //////////////////////////////////////////
            if (event.key.code == sf::Keyboard::Up)
                isShootingUp = false;
            if (event.key.code == sf::Keyboard::Right)
                isShootingRight = false;
            if (event.key.code == sf::Keyboard::Down)
                isShootingDown = false;
            if (event.key.code == sf::Keyboard::Left)
                isShootingLeft = false;
            //////////////////////////////////////////

        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // Получаем координаты нажатия
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            // Получаем координаты игрока
            sf::FloatRect player_pos = p.rec.getGlobalBounds();

            p.shooting(mouseX - player_pos.left, mouseY - player_pos.top, clock.getElapsedTime().asMilliseconds());
        }
    }

    if (isMovingUp){
        p.dy = -1;
        p.moving(b);
        p.dy = 0;
        p.rotate(0, -1);
    }
    if (isMovingRight){
        p.dx = 1;
        p.moving(b);
        p.dx = 0;
        p.rotate(1, 0);
    }
    if (isMovingDown){
        p.dy = 1;
        p.moving(b);
        p.dy = 0;
        p.rotate(0, 1);
    }
    if (isMovingLeft){
        p.dx = -1;
        p.moving(b);
        p.dx = 1;
        p.rotate(-1, 0);
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
                    if (enemy.alive && p.gun.magazine[i].check_collision(enemy.rec.getGlobalBounds())){
                        enemy.alive = false;
                    }
                    p.gun.magazine[i].check_collision(b);
                }
            }
        }
    }

    // if (!p.alive){
    //     restart();
    // }
}

// void GameEngine::restart(void){
//     //генерим новую карту
//     for (int i = 0; i < 12; ++i){
//         std::cout << i << " : "<<b.cells[i].is_up << b.cells[i].is_right << b.cells[i].is_down << b.cells[i].is_left <<std::endl;
//     }
//     b = Board(screen_w, screen_h, 10, 15);
//     for (int i = 0; i < 12; ++i){
//         std::cout << i << " : "<<b.cells[i].is_up << b.cells[i].is_right << b.cells[i].is_down << b.cells[i].is_left <<std::endl;
//     }
//     b.dfs(0,0);
//     //новый игрок
//     p = Hero(texHero, 10.f, 10.f, HERO_WIDTH, HERO_HEIGHT);
//     p.gun = Gun(texBullet, 30, 200.f, 6, 2000.f);
//     //генерим игроков
//     enemies.clear();
//     float rand_cor_x;
//     float rand_cor_y;
//     for (int i = 0; i < ENEMY_COUNT; ++i){
//         rand_cor_x = (rand() % b.n) * b.cell_w + b.cell_w / 2 - ENEMY_WIDTH / 2;
//         rand_cor_y = (rand() % b.m) * b.cell_h + b.cell_h / 2 - ENEMY_HEIGHT / 2;

//         enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, ENEMY_WIDTH, ENEMY_HEIGHT);
//         enemies[i].gun = Gun(texBullet, 10, 500.f, 3, 2000.f);
//     }
//     // сбрасываем часы
//     clock.restart();
// }