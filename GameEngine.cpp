#include "GameEngine.hpp"

GameEngine::GameEngine(void)
: window(sf::VideoMode::getDesktopMode(), "Recycler", sf::Style::Fullscreen){

    if (!this->texHero.loadFromFile("hero.png"))std::cerr<<"No such file for hero";
    if (!this->texEnemy.loadFromFile("enemy.png"))std::cerr<<"No such file for enemy";
    if (!this->texBullet.loadFromFile("bullet.png"))std::cerr<<"No such file for bullet";
    if (!this->textFont.loadFromFile("src/Roboto-Black.ttf"))std::cerr << "No such file for text" << std::endl;


    this->screen_w = window.getSize().x;
    this->screen_h = window.getSize().y;

    this->n = 6;
    this->m = 5;

    sf::Image icon;
    if (!icon.loadFromFile("src/icon.png"))std::cerr << "No such file with icon" << std::endl;
    window.setIcon(32, 32, icon.getPixelsPtr());


	window.setFramerateLimit(60);

	b = Board(screen_w * 3.f/4.f, screen_h, n, m);

    this->human_size = static_cast<int>(screen_w / n) * 1.f/4.f;

    this->player_health = 40;
    this->player_speed = 6;
    this->player_damage = 10;
	p = Hero(texHero, 10.f, 10.f, human_size, human_size, player_health, player_speed, player_damage);
    nbullets_in_player_gun = 6;
    p.gun = Gun(texBullet, nbullets_in_player_gun, 200.f, BULLET_SPEED, 2000.f);


    this->num_enemy = std::max(n, m);
    this->enemies_alive = num_enemy;
    this->nbullets_in_enemy_gun = 12;
    this->enemy_speed = 4;
    this->enemy_health = 20;
    this->enemy_damage = 10;

    std::set<std::pair<int, int>> enemy_pozitions;
    enemy_pozitions.insert(std::make_pair(0, 0));
    enemies.clear();
    float rand_cor_x, rand_cor_y, rand_col, rand_row;
    for (int i = 0; i < num_enemy; ++i){
        rand_col = (rand() % b.n);
        rand_row = (rand() % b.m);
        while (0 != enemy_pozitions.count(std::make_pair(rand_col, rand_row))){
            rand_col = (rand() % b.n);
            rand_row = (rand() % b.m);
        }
        enemy_pozitions.insert(std::make_pair(rand_col, rand_row));
        rand_cor_x = rand_col * b.cell_w + b.cell_w / 2 - human_size / 2;
        rand_cor_y = rand_row * b.cell_h + b.cell_h / 2 - human_size / 2;
        enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, human_size, human_size, enemy_health, enemy_speed, enemy_damage);
        enemies[i].gun = Gun(texBullet, nbullets_in_enemy_gun, 500.f, BULLET_SPEED, 4000.f);
    }

    /////INFO PANEL/////////
    infPanel.setFillColor(sf::Color(80,80,80));
    infPanel.setPosition(screen_w * 3.f/4.f, 0);
    infPanel.setSize(sf::Vector2f(screen_w * 1.f/4.f, static_cast<float>(screen_h)));
    
    this->cur_level = 1;
    levelText = sf::Text("Level: " + std::to_string(cur_level), textFont);
    levelText.setCharacterSize(30);
    levelText.setStyle(sf::Text::Bold);
    levelText.setFillColor(sf::Color::Red);
    levelText.setPosition(screen_w * 3.f/4.f + 120.f, 0);

    nbulletsText = sf::Text("Bullets: " + std::to_string(nbullets_in_player_gun) + "/" + std::to_string(nbullets_in_player_gun), textFont);
    nbulletsText.setCharacterSize(20);
    nbulletsText.setFillColor(sf::Color::Red);
    nbulletsText.setPosition(screen_w * 3.f/4.f + 60.f, 50);

    gunStatusText = sf::Text("Gun status: Ready", textFont);
    gunStatusText.setCharacterSize(20);
    gunStatusText.setFillColor(sf::Color::Red);
    gunStatusText.setPosition(screen_w * 3.f/4.f + 60.f, 100);

    healthText = sf::Text("Health: " + std::to_string(p.health) + "/" + std::to_string(player_health), textFont);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(screen_w * 3.f/4.f + 60.f, 150);

    nenemyText = sf::Text("Enemy alive: " + std::to_string(enemies_alive), textFont);
    nenemyText.setCharacterSize(20);
    nenemyText.setFillColor(sf::Color::Red);
    nenemyText.setPosition(screen_w * 3.f/4.f + 60.f, 200);

    moneyText = sf::Text("Money: " + std::to_string(money_count), textFont);
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::Red);
    moneyText.setPosition(screen_w * 3.f/4.f + 60.f, 250);
    ////////////////////////
    //////////////////////
    healthButton.setSize(sf::Vector2f(160.f, 30.f));
    healthButton.setPosition(screen_w * 3.f/4.f + 60.f, 300);
    healthButton.setFillColor(sf::Color::White);

    healthWord = sf::Text("Health UP cost: 10", textFont);
    healthWord.setCharacterSize(15);
    healthWord.setFillColor(sf::Color::Black);
    healthWord. setPosition(screen_w * 3.f/4.f + 60.f, 300);
    //////////////////////
    damageButton.setSize(sf::Vector2f(160.f, 30.f));
    damageButton.setPosition(screen_w * 3.f/4.f + 60.f, 350);
    damageButton.setFillColor(sf::Color::White);

    damageWord = sf::Text("Damage UP cost: 10", textFont);
    damageWord.setCharacterSize(15);
    damageWord.setFillColor(sf::Color::Black);
    damageWord.setPosition(screen_w * 3.f/4.f + 60.f, 350);
    //////////////////////

    bulletButton.setSize(sf::Vector2f(160.f, 30.f));
    bulletButton.setPosition(screen_w * 3.f/4.f + 60.f, 400);
    bulletButton.setFillColor(sf::Color::White);

    bulletWord = sf::Text("Bullets UP cost: 10", textFont);
    bulletWord.setCharacterSize(15);
    bulletWord.setFillColor(sf::Color::Black);
    bulletWord.setPosition(screen_w * 3.f/4.f + 60.f, 400);



    ////////////////////////

    this->money_count = 0;
    clock.restart();
}

GameEngine::~GameEngine(){
}

void GameEngine::run(void){
	b.dfs(0, 0);
    b.was.clear();


	while (window.isOpen()){
		input();
		draw();
	}
}

void GameEngine::draw(void){
	window.clear();
	b.draw(window);
	p.draw(window);

    for (int i = 0; i < num_enemy; ++i){
        enemies[i].draw(window);
    }

    window.draw(infPanel);
    window.draw(levelText);
    window.draw(nbulletsText);
    window.draw(gunStatusText);
    window.draw(healthText);
    window.draw(nenemyText);
    window.draw(moneyText);

    window.draw(healthButton);
    window.draw(healthWord);

    window.draw(damageButton);
    window.draw(damageWord);

    window.draw(bulletButton);
    window.draw(bulletWord);

	window.display();
}

void GameEngine::input(void) {
    p.dx = 0;
    p.dy = 0;

    float cur_time = clock.getElapsedTime().asMilliseconds();

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
    if (isShootingUp) p.shooting(0, -1, cur_time);
    if (isShootingRight) p.shooting(1, 0, cur_time);
    if (isShootingDown) p.shooting(0, 1, cur_time);
    if (isShootingLeft) p.shooting(-1, 0, cur_time);

    for (auto& enemy : enemies){
        enemy.moving(b, p);
        if (p.health <= 0) break;
        enemy.shooting(b, p, cur_time);
    }
    if (p.health > 0 && enemies_alive != 0){
        for (int i = 0; i < p.gun.magazine_size - p.gun.bullets_in_gun; ++i){
            for (int j = 0; j < p.gun.speed_bullet; ++j){
                p.gun.magazine[i].moving();
                if (!p.gun.magazine[i].was_collision){
                    for (auto& enemy : enemies){
                        if (enemy.health > 0 && p.gun.magazine[i].check_collision(enemy.rec.getGlobalBounds())){
                            enemy.health -= p.damage;
                            if (enemy.health <= 0)money_count += 1;
                        }             
                        p.gun.magazine[i].check_collision(b);
                    }
                }
            }
        }
        enemies_alive = 0;
        for (const auto& enemy : enemies){
            enemies_alive += (enemy.health > 0);
        }
        nbulletsText.setString("Bullets: " + std::to_string(p.gun.get_nbullets(cur_time)) + "/" + std::to_string(p.gun.magazine_size));
        if (p.gun.is_recharging(cur_time))gunStatusText.setString("Gun status: Recharging");
        else gunStatusText.setString("Gun status: Ready");
        healthText.setString("Health: " + std::to_string(p.health) + "/" + std::to_string(player_health));
        nenemyText.setString("Enemy alive: " + std::to_string(enemies_alive));
        moneyText.setString("Money: " + std::to_string(money_count));

    }
    else if(enemies_alive == 0){
        restart();
    }
    else {
        window.close();//todo 
    }
}

void GameEngine::restart(void){
    
    //генерим новую карту
    this->n += 2;
    this->m += 1;
    b = Board(screen_w * 3.f/4.f, screen_h, n, m);
    b.dfs(0,0);
    b.was.clear();

    //новый игрок
    this->human_size = static_cast<int>(screen_w / n) * 1.f/4.f;

    p = Hero(texHero, 10.f, 10.f, human_size, human_size, player_health, player_speed, player_damage);
    p.gun = Gun(texBullet, nbullets_in_player_gun, 200.f, BULLET_SPEED, 2000.f);
    //генерим игроков
    this->num_enemy = std::max(n, m);

    std::set<std::pair<int, int>> enemy_pozitions;
    enemy_pozitions.insert(std::make_pair(0, 0));
    enemies.clear();
    float rand_cor_x, rand_cor_y, rand_col, rand_row;
    for (int i = 0; i < num_enemy; ++i){
        rand_col = (rand() % b.n);
        rand_row = (rand() % b.m);
        while (0 != enemy_pozitions.count(std::make_pair(rand_col, rand_row))){
            rand_col = (rand() % b.n);
            rand_row = (rand() % b.m);
        }
        enemy_pozitions.insert(std::make_pair(rand_col, rand_row));
        rand_cor_x = rand_col * b.cell_w + b.cell_w / 2 - human_size / 2;
        rand_cor_y = rand_row * b.cell_h + b.cell_h / 2 - human_size / 2;
        enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, human_size, human_size, enemy_health, enemy_speed, enemy_damage);
        enemies[i].gun = Gun(texBullet, 10, 500.f, BULLET_SPEED, 2000.f);
    }

    enemies_alive = num_enemy;

    cur_level += 1;
    levelText.setString("Level: " + std::to_string(cur_level));


    // сбрасываем часы
    clock.restart();
}