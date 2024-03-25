#include "GameEngine.hpp"

GameEngine::GameEngine(void)
: window(sf::VideoMode::getDesktopMode(), "Recycler", sf::Style::Fullscreen){
    // загрузка ресурсов
    if (!this->texHero.loadFromFile("src/hero.png"))std::cerr << "No such file for hero";
    if (!this->texEnemy.loadFromFile("src/enemy.png"))std::cerr << "No such file for enemy";
    if (!this->texBullet.loadFromFile("src/bullet.png"))std::cerr << "No such file for bullet";
    if (!this->textFont.loadFromFile("src/Roboto-Black.ttf"))std::cerr << "No such file for text";
    if (!this->texBackground.loadFromFile("src/background.jpg"))std::cerr << "No such file for background";
    if (!this->shootSoundBuffer.loadFromFile("src/shootSound.wav"))std::cerr << "No such file for shoot sound";
    if (!this->rechargeSoundBuffer.loadFromFile("src/rechargeSound.wav"))std::cerr << "No such file for recharge sound";
    if (!this->infoTex.loadFromFile("src/rules.jpg"))std::cerr << "No such file for rules";

    // получаем размеры экрана
    this->screen_w = window.getSize().x;
    this->screen_h = window.getSize().y;

    //устанавливаем текстуру на задний фон
    backgroundSprite.setTexture(texBackground);

    //масштабируем background sprite
    sf::FloatRect backgroundBounds = backgroundSprite.getGlobalBounds();
    float imageScale_x = screen_w / backgroundBounds.width;
    float imageScale_y = screen_h / backgroundBounds.height;
    backgroundSprite.setScale(imageScale_x, imageScale_y);
    //устанавливаем спрайт
    backgroundSprite.setPosition(0, 0);

    //устанавливаем текстуру для правил игры
    infoSprite.setTexture(infoTex);
    //масштабируем sprite
    sf::FloatRect infoBounds = infoSprite.getGlobalBounds();
    imageScale_x = screen_w / infoBounds.width;
    imageScale_y = screen_h / infoBounds.height;
    infoSprite.setScale(imageScale_x, imageScale_y);
    //устанавливаем спрайт
    infoSprite.setPosition(0, 0);

    // загружаем и устанавливаем иконку игры
    sf::Image icon;
    if (!icon.loadFromFile("src/icon.jpg"))std::cerr << "No such file with icon" << std::endl;
    window.setIcon(376, 371, icon.getPixelsPtr());

    // устанавливаем частотц кадров 60fps
	window.setFramerateLimit(60);

    // инициализируем звуки стрельбы и перезарядки
    shootSound.setBuffer(shootSoundBuffer);
    rechargeSound.setBuffer(rechargeSoundBuffer);

    /////инициализируем панель состояния игрока и оружия/////////
    infPanel.setFillColor(sf::Color(80,80,80));
    infPanel.setPosition(screen_w * 3.f/4.f, 0);
    infPanel.setSize(sf::Vector2f(screen_w * 1.f/4.f, static_cast<float>(screen_h)));
    
    this->cur_level = 1;
    levelText = sf::Text("Level: " + std::to_string(cur_level), textFont);
    levelText.setCharacterSize(30);
    levelText.setStyle(sf::Text::Bold);
    levelText.setFillColor(sf::Color::Red);
    levelText.setPosition(screen_w * 3.f/4.f + 120.f, 50);

    nbulletsText = sf::Text("Bullets: " + std::to_string(nbullets_in_player_gun) + "/" + std::to_string(nbullets_in_player_gun), textFont);
    nbulletsText.setCharacterSize(20);
    nbulletsText.setFillColor(sf::Color::Red);
    nbulletsText.setPosition(screen_w * 3.f/4.f + 60.f, 100);

    gunStatusText = sf::Text("Gun status: Ready", textFont);
    gunStatusText.setCharacterSize(20);
    gunStatusText.setFillColor(sf::Color::Red);
    gunStatusText.setPosition(screen_w * 3.f/4.f + 60.f, 150);

    healthText = sf::Text("Health: " + std::to_string(p.health) + "/" + std::to_string(player_health), textFont);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(screen_w * 3.f/4.f + 60.f, 200);

    nenemyText = sf::Text("Enemy alive: " + std::to_string(enemies_alive), textFont);
    nenemyText.setCharacterSize(20);
    nenemyText.setFillColor(sf::Color::Red);
    nenemyText.setPosition(screen_w * 3.f/4.f + 60.f, 250);

    moneyText = sf::Text("Money: " + std::to_string(money_count), textFont);
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::Red);
    moneyText.setPosition(screen_w * 3.f/4.f + 60.f, 300);


    /////////////////////////////////////////////////////////////
    //////инициализируем кнопки улучшений и управления///////////
    /////////////////////////////////////////////////////////////

    //////////////////////////////
    // кнопка прокачки здоровья //
    //////////////////////////////
    healthButton.setSize(sf::Vector2f(160.f, 30.f));
    healthButton.setPosition(screen_w * 3.f/4.f + 60.f, 350);
    healthButton.setFillColor(sf::Color::Black);

    healthWord = sf::Text("Health UP cost: 10", textFont);
    healthWord.setCharacterSize(15);
    healthWord.setFillColor(sf::Color::White);
    healthWord. setPosition(screen_w * 3.f/4.f + 60.f + 5.f, 350);

    ///////////////////////////
    // кнопка прокачки урона //
    ///////////////////////////
    damageButton.setSize(sf::Vector2f(160.f, 30.f));
    damageButton.setPosition(screen_w * 3.f/4.f + 60.f, 400);
    damageButton.setFillColor(sf::Color::Black);

    damageWord = sf::Text("Damage UP cost: 10", textFont);
    damageWord.setCharacterSize(15);
    damageWord.setFillColor(sf::Color::White);
    damageWord.setPosition(screen_w * 3.f/4.f + 60.f + 5.f, 400);

    /////////////////////////////////////////
    // кнопка прокачки количества патронов //
    /////////////////////////////////////////
    bulletButton.setSize(sf::Vector2f(160.f, 30.f));
    bulletButton.setPosition(screen_w * 3.f/4.f + 60.f, 450);
    bulletButton.setFillColor(sf::Color::Black);

    bulletWord = sf::Text("Bullets UP cost: 10", textFont);
    bulletWord.setCharacterSize(15);
    bulletWord.setFillColor(sf::Color::White);
    bulletWord.setPosition(screen_w * 3.f/4.f + 60.f + 5.f, 450);

    //////////////////////////////////////////
    // кнопка перехода на следующий уровень //
    //////////////////////////////////////////
    nextLevelButton.setSize(sf::Vector2f(160.f, 30.f));
    nextLevelButton.setPosition(screen_w * 3.f/4.f + 60.f, 500);
    nextLevelButton.setFillColor(sf::Color::Black);

    nextLevelWord = sf::Text("Next Level", textFont);
    nextLevelWord.setCharacterSize(15);
    nextLevelWord.setFillColor(sf::Color::White);
    nextLevelWord.setPosition(screen_w * 3.f/4.f + 60.f + 40.f, 500);

    //////////////////////////
    // кнопка выхода в меню //
    //////////////////////////
    menuButton.setSize(sf::Vector2f(160.f, 30.f));
    menuButton.setPosition(screen_w * 3.f/4.f + 60.f, screen_h * 9.f/10.f);
    menuButton.setFillColor(sf::Color::Black);

    menuWord = sf::Text("Menu", textFont);
    menuWord.setCharacterSize(20);
    menuWord.setFillColor(sf::Color::White);
    menuWord.setPosition(screen_w * 3.f/4.f + 60.f + 55.f, screen_h * 9.f/10.f);

    ////////////////////////
    // кнопка начала игры //
    ////////////////////////    
    startButton.setSize(sf::Vector2f(200.f, 60.f));
    startButton.setPosition(screen_w - 200.f, 670);
    startButton.setFillColor(sf::Color::Black);

    startWord = sf::Text("START", textFont);
    startWord.setCharacterSize(50);
    startWord.setFillColor(sf::Color::White);
    startWord.setPosition(screen_w - 200.f, 670);

    ////////////////////////////////
    // кнопка настройки громкости //
    ////////////////////////////////
    volumeButton.setSize(sf::Vector2f(200.f, 60.f));
    volumeButton.setPosition(screen_w - 200.f, 0);
    volumeButton.setFillColor(sf::Color::Black);

    volumeWord = sf::Text("VOLUME", textFont);
    volumeWord.setCharacterSize(50);
    volumeWord.setFillColor(sf::Color::White);
    volumeWord.setPosition(screen_w - 200.f, 0);

    //////////////////////////////
    // кнопка информации о игре //
    //////////////////////////////
    infoButton.setSize(sf::Vector2f(200.f, 40.f));
    infoButton.setPosition(screen_w - 200.f, 620);
    infoButton.setFillColor(sf::Color::Black);

    infoWord = sf::Text("INFO", textFont);
    infoWord.setCharacterSize(30);
    infoWord.setFillColor(sf::Color::White);
    infoWord.setPosition(screen_w - 200.f, 620);

    ////////////////////////////////////
    // label для меню настройки звука //
    ////////////////////////////////////
    volumeText = sf::Text("Volume", textFont);
    volumeText.setCharacterSize(50);
    volumeText.setFillColor(sf::Color::Black);
    volumeText.setPosition(100.f, 1.f/2.f * screen_h);
}

/*
    Деструктор класса GameEngine
*/
GameEngine::~GameEngine(){
}

/*
    Функция отображения главного меню игры
*/
void GameEngine::menu(void){
    bool isStart = false;
    while (window.isOpen() && !isStart){
        // рисуем обЪекты главного меню
        window.clear();
        window.draw(backgroundSprite);
        window.draw(startButton);
        window.draw(startWord);
        window.draw(volumeButton);
        window.draw(volumeWord);
        window.draw(infoButton);
        window.draw(infoWord);
        window.display();

        // обработка нажатия элементов главного меню
        sf::Event event;
        while (window.pollEvent(event)) {
            // отслеживание закрытия окна
            if (event.type == sf::Event::Closed)
                window.close();
            // отслеживание нажатия клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter){
                    isStart = true;
                }

            }
            // отслеживание нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                // Получаем координаты нажатия
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                // смотрим пересечения с элементами интерфейса
                // пересечение с кнопкой START
                if (startButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    isStart = true;
                }
                // пересечение с кнопкой настройки громкости
                if (volumeButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    this->volumeSettings();
                }
                // пересечения с кнопкой INFO
                if (infoButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    this->showInfo();
                }
            }
        }
    }   
}

/*
    Меню настройки громкости игры
        - ползунок настраивает громкость звуковых эффектов стрельбы и перезарядки
*/
void GameEngine::volumeSettings(void){
    // инициализация прямоугольника по которму будет бегать слайдер
    sf::RectangleShape volumeBar(sf::Vector2f(1.f/3.f * screen_w, 20));
    volumeBar.setPosition(1.f/3.f * screen_w, 1.f/2.f * screen_h);
    volumeBar.setFillColor(sf::Color(80, 80, 80));

    // инициализация прямоугольника слайдера
    sf::RectangleShape volumeSlider(sf::Vector2f(20, 40));
    volumeSlider.setPosition(1.f/3.f * screen_w, 1.f/2.f * screen_h);
    volumeSlider.setFillColor(sf::Color::White);

    // начальное положение ползунка громкости
    int volume = 0;

    bool isMenu = false;
    while (window.isOpen() && !isMenu){
        // отрисовка элементов меню настройки громкости
        window.clear();
        window.draw(backgroundSprite);
        window.draw(menuButton);
        window.draw(menuWord);
        window.draw(volumeBar);
        window.draw(volumeSlider);
        window.draw(volumeText);
        window.display();

        // обработка нажатий элементов меню громкости
        sf::Event event;
        while (window.pollEvent(event)) {
            // отслеживание закрытия окна
            if (event.type == sf::Event::Closed)
                window.close();
            // отслеживание нажатия клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter){
                    isMenu = true;
                }
            }
            // отслеживание нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Получаем координаты нажатия
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                //проверям пересечение с кнопкой Menu
                if (startButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    isMenu = true;
                }

            }
            // обработка скроллинга слайдера
            else if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (mousePos.x >= (1.f/3.f * screen_w) && mousePos.x <= (2.f/3.f * screen_w))
                    {
                        volumeSlider.setPosition(mousePos.x - 10, 1.f/2.f * screen_h);
                        volume = (mousePos.x - (1.f/3.f * screen_w)) / (1.f/3.f * screen_w) * 100;
                        volumeText.setString("Volume: " + std::to_string(volume));
                        shootSound.setVolume(volume);
                        rechargeSound.setVolume(volume);
                    }
                }
            }
        }
    }   
}

/*
    отрисовка элементов интерфейса меню информации об игре
        - кнопка Menu
*/
void GameEngine::showInfo(void){
    bool isMenu = false;
    while (window.isOpen() && !isMenu){
        // отрисовка элементов информации об игре
        window.clear();
        window.draw(infoSprite);
        window.draw(menuButton);
        window.draw(menuWord);
        window.display();

        // обработка нажатий элементов информации об игре
        sf::Event event;
        while (window.pollEvent(event)) {
            // отслеживание закрытия окна
            if (event.type == sf::Event::Closed)
                window.close();
            // отслеживание нажатия клавиш
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter){
                    isMenu = true;
                }
            }
            // отслеживание нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Получаем координаты нажатия
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                if (menuButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    isMenu = true;
                }

            }
        }
    }  
}

/*
    функция изначальной инициализации элементов игры
*/
void GameEngine::startInit(void){
    // устанавливаем стартовые размеры поля в клетках
    this->n = 6;
    this->m = 5;
    // инициализируем игровое поле
    b = Board(screen_w * 3.f/4.f, screen_h, n, m);
    // генерируем случайное положение стен лабиринта
    b.dfs(0, 0);
    b.was.clear();

    // устанавливаем начальное значение текущего уровня
    this->cur_level = 1;
    // подготавливаем label с текущим уровнем игры
    levelText.setString("Level: " + std::to_string(cur_level));

    //сбрасываем направление движения и стрельбы персонажа
    isMovingUp = false; isMovingDown = false; isMovingLeft = false; isMovingRight = false;
    isShootingUp = false; isShootingDown = false; isShootingLeft = false; isShootingRight = false;

    // расчитываем размер спрайта персонажа
    this->human_size = static_cast<int>(screen_w / n) * 1.f/4.f;

    // устанавливаем начальные характеристики персонажа
    this->player_health = 40;
    this->player_speed = 6;
    this->player_damage = 10;
    // инициализируем персонажа
    p = Hero(texHero, 10.f, 10.f, human_size, human_size, player_health, player_speed, player_damage);
    // инициализируем оружие персонажа
    nbullets_in_player_gun = 6;
    p.gun = Gun(texBullet, nbullets_in_player_gun, 200.f, BULLET_SPEED, 2000.f);

    // подготавливаем врагов
    // инициализируем характеристики врагов
    this->num_enemy = std::max(n, m);
    this->enemies_alive = num_enemy;
    this->nbullets_in_enemy_gun = 12;
    this->enemy_speed = 4;
    this->enemy_health = 20;
    this->enemy_damage = 10;
    // расставляем врагов
    std::set<std::pair<int, int>> enemy_pozitions;
    // нельзя ставить врагов в ту же клетку где находится персонаж
    enemy_pozitions.insert(std::make_pair(0, 0));
    enemies.clear();
    float rand_cor_x, rand_cor_y, rand_col, rand_row;
    // для инициализируем num_enemy врагов
    for (int i = 0; i < num_enemy; ++i){
        // получаем случайные координаты из поля n x m
        rand_col = (rand() % b.n);
        rand_row = (rand() % b.m);
        // пока случайные координаты не стали уникальными
        while (0 != enemy_pozitions.count(std::make_pair(rand_col, rand_row))){ 
            // генерируем их снова и снова
            rand_col = (rand() % b.n);
            rand_row = (rand() % b.m);
        }
        // если нашлись уникальные координаты, то запомниаем их
        enemy_pozitions.insert(std::make_pair(rand_col, rand_row));
        // и расчитываем положение врага относительно левого верзнего угла в пикселях
        rand_cor_x = rand_col * b.cell_w + b.cell_w / 2 - human_size / 2;
        rand_cor_y = rand_row * b.cell_h + b.cell_h / 2 - human_size / 2;
        // добавляем нового врга в массив врагов
        enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, human_size, human_size, enemy_health, enemy_speed, enemy_damage);
        // выдаем новому врагу оружие
        enemies[i].gun = Gun(texBullet, nbullets_in_enemy_gun, 500.f, BULLET_SPEED, 2000.f);
    }
    // инициализируем текущее количество монет
    this->money_count = 0;
    // сбрасываем игровой таймер
    clock.restart();
}

/*
    функция запуска игры
*/
void GameEngine::run(void){
    while (window.isOpen()){
        menu();
        startInit();
        while (window.isOpen() && p.health > 0){
            input();
            draw();
        }
    }	
}

/*
    функция отрисовки основных элементов игрового процесса
*/
void GameEngine::draw(void){
    // очищаем окно от предыдущих спрайтов
	window.clear();
    // изображаем игровое поле
	b.draw(window);
    // изображаем игрока
	p.draw(window);
    // изображаем врагов
    for (int i = 0; i < num_enemy; ++i){
        enemies[i].draw(window);
    }

    // изображаем панель состояния игрока
    window.draw(infPanel);
    window.draw(levelText);
    window.draw(nbulletsText);
    window.draw(gunStatusText);
    window.draw(healthText);
    window.draw(nenemyText);
    window.draw(moneyText);
    window.draw(menuButton);
    window.draw(menuWord);

    // рисуем текущий фрэйм
	window.display();
}

/*
    обработка ввода игрового процесса
*/
void GameEngine::input(void) {
    // сбрасываем направление персонажа
    p.dx = 0;
    p.dy = 0;

    // получаем текущее время
    float cur_time = clock.getElapsedTime().asMilliseconds();

    // обработка событий игрового процесса
    sf::Event event;
    while (window.pollEvent(event)) {
        // отслеживание закрытия окна
        if (event.type == sf::Event::Closed)
            window.close();
        // отслеживание нажатия кнопок
        if (event.type == sf::Event::KeyPressed) {

            // нажатие кнопок перемещения персонажа (WASD)
            if (event.key.code == sf::Keyboard::W)
                isMovingUp = true;

            if (event.key.code == sf::Keyboard::D)
                isMovingRight = true;

            if (event.key.code == sf::Keyboard::S)
                isMovingDown = true;

            if (event.key.code == sf::Keyboard::A)
                isMovingLeft = true;

            // нажатие кнопок стрельбы персонаж (стрелки)
            if (event.key.code == sf::Keyboard::Up)
                isShootingUp = true;

            if (event.key.code == sf::Keyboard::Right)
                isShootingRight = true;

            if (event.key.code == sf::Keyboard::Down)
                isShootingDown = true;

            if (event.key.code == sf::Keyboard::Left)
                isShootingLeft = true;
        }
        // отслеживание отпускания клавиш
        if (event.type == sf::Event::KeyReleased) {

            // отпускание кнопок перемещения персонажа (WASD)
            if (event.key.code == sf::Keyboard::W)
                isMovingUp = false;

            if (event.key.code == sf::Keyboard::D)
                isMovingRight = false;

            if (event.key.code == sf::Keyboard::S)
                isMovingDown = false;

            if (event.key.code == sf::Keyboard::A)
                isMovingLeft = false;

            // отпускание кнопок стрельбы персонаж (стрелки)
            if (event.key.code == sf::Keyboard::Up)
                isShootingUp = false;

            if (event.key.code == sf::Keyboard::Right)
                isShootingRight = false;

            if (event.key.code == sf::Keyboard::Down)
                isShootingDown = false;

            if (event.key.code == sf::Keyboard::Left)
                isShootingLeft = false;
        }
        // отслеживание нажатий мыши
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // Получаем координаты нажатия
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            // Получаем координаты игрока
            sf::FloatRect player_pos = p.rec.getGlobalBounds();
            // персонаж стреляет в заданом направлении
            p.shooting(mouseX - player_pos.left, mouseY - player_pos.top, shootSound, rechargeSound, clock.getElapsedTime().asMilliseconds());
            // проверяем пересечение с кнопокой Menu
            if (menuButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                // для выхода в Menu убиваем персонажа
                p.health = 0;
            }
        }
    }
    // обработка полученных направлений движения персонажа
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

    // выстрел в полученном направлении персонажа
    if (isShootingUp) p.shooting(0, -1, shootSound, rechargeSound, cur_time);
    if (isShootingRight) p.shooting(1, 0, shootSound, rechargeSound, cur_time);
    if (isShootingDown) p.shooting(0, 1, shootSound, rechargeSound, cur_time);
    if (isShootingLeft) p.shooting(-1, 0, shootSound, rechargeSound, cur_time);

    // для всех врагов выполняем метод shooting
    for (auto& enemy : enemies){
        enemy.moving(b, p);
        if (p.health <= 0) break;
        enemy.shooting(b, p, shootSound, rechargeSound, cur_time);
    }
    // передвигаем патроны выпущенные персонажем
    if (p.health > 0 && enemies_alive != 0){
        for (int i = 0; i < p.gun.magazine_size - p.gun.bullets_in_gun; ++i){
            for (int j = 0; j < p.gun.speed_bullet; ++j){
                p.gun.magazine[i].moving();
                // если патрон еще не с чем не сталкивался
                if (!p.gun.magazine[i].was_collision){
                    // проверяем столкновение со всеми врагами которых можно убить
                    for (auto& enemy : enemies){
                        // если произошло пересечение с живым врагом
                        if (enemy.health > 0 && p.gun.magazine[i].check_collision(enemy.rec.getGlobalBounds())){
                            // уменьшаем здоровье врага
                            enemy.health -= p.damage;
                            // в случае смерти врага увеличиваем счетчик монет
                            if (enemy.health <= 0)money_count += 1;
                        }
                        // проверяем столкновение пули с лабиринтом
                        p.gun.magazine[i].check_collision(b);
                    }
                }
            }
        }
        // подсчитываем количество живых врагов
        enemies_alive = 0;
        for (const auto& enemy : enemies){
            enemies_alive += (enemy.health > 0);
        }
        // обновляем label с информацией о:
        // количестве патронов
        nbulletsText.setString("Bullets: " + std::to_string(p.gun.get_nbullets(cur_time)) + "/" + std::to_string(p.gun.magazine_size));
        // статусе оружия
        if (p.gun.is_recharging(cur_time))gunStatusText.setString("Gun status: Recharging");
        else gunStatusText.setString("Gun status: Ready");
        // здоровья персонажа
        healthText.setString("Health: " + std::to_string(p.health) + "/" + std::to_string(player_health));
        // количество живых врагов
        nenemyText.setString("Enemy alive: " + std::to_string(enemies_alive));
        // количестов собраных монет
        moneyText.setString("Money: " + std::to_string(money_count));

    }
    // елси не осталось живых врагов 
    else if(enemies_alive == 0){
        // запускаем функцию генерации следующего уровня
        restart();
    }
}

/*
    Функция инициализации перехода на следующий уровень
*/
void GameEngine::restart(void){
    bool need_next_level = false;
    // обработка ввода
    sf::Event event;
    while (window.isOpen() && !need_next_level){
        // получаем текущее время
        float cur_time = clock.getElapsedTime().asMilliseconds();
        // обновляем состояние label ов
        nbulletsText.setString("Bullets: " + std::to_string(p.gun.get_nbullets(cur_time)) + "/" + std::to_string(p.gun.magazine_size));
        if (p.gun.is_recharging(cur_time))gunStatusText.setString("Gun status: Recharging");
        else gunStatusText.setString("Gun status: Ready");
        healthText.setString("Health: " + std::to_string(p.health) + "/" + std::to_string(player_health));
        nenemyText.setString("Enemy alive: " + std::to_string(enemies_alive));
        moneyText.setString("Money: " + std::to_string(money_count));

        // отрисовываем игровые объекты
        // отрисовка поля и игрока
        window.clear();
        b.draw(window);
        p.draw(window);
        // отрисовка варгов
        for (int i = 0; i < num_enemy; ++i){
            enemies[i].draw(window);
        }
        // отрисовка панели состояния игрока
        window.draw(infPanel);
        window.draw(levelText);
        window.draw(nbulletsText);
        window.draw(gunStatusText);
        window.draw(healthText);
        window.draw(nenemyText);
        window.draw(moneyText);

        // отрисовка кнопки улучшения здоровья
        window.draw(healthButton);
        window.draw(healthWord);
        // отрисовка кнопки увеличения урона оружия
        window.draw(damageButton);
        window.draw(damageWord);
        // отрисовка кнопки увеличения числа патронов
        window.draw(bulletButton);
        window.draw(bulletWord);
        // отрисовка кнопки выхода в главное меню
        window.draw(menuButton);
        window.draw(menuWord);
        // отрисовка кнопки перехода на следующий уровень
        window.draw(nextLevelButton);
        window.draw(nextLevelWord);
        // отображение интерфейса
        window.display();

        // обработка событий игрового процесса
        while (window.pollEvent(event)) {
            // отслеживание закрытия окна
            if (event.type == sf::Event::Closed)
                window.close();
            // отслеживание нажатий мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Получаем координаты нажатия
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // проверяем пересечение с кнопокой улучшения здоровья
                if (healthButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    if (money_count >= 10){
                        player_health += 10;
                        money_count -= 10;
                    }
                }

                // проверяем пересечение с кнопкой увеличения урона
                else if (damageButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    if (money_count >= 10){
                        player_damage += 1;
                        money_count -= 10;
                    }
                }

                // проверяем пересечение с кнопкой увеличения числа патронов
                else if (bulletButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    if (money_count >= 10){
                        this->nbullets_in_player_gun += 1;
                        money_count -= 10;
                    }
                }

                // проверяем пересечение с кнопкой перехода на следующий уровень
                else if (nextLevelButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    need_next_level = true;
                }

                // проверяем пересечение с кнопкой выхода в главное меню
                else if (menuButton.getGlobalBounds().contains(sf::Vector2f(mouseX, mouseY))){
                    p.health = 0;
                    return;
                }
            }
        }
    }

    //сбрасываем направление движения и стрельбы
    isMovingUp = false; isMovingDown = false; isMovingLeft = false; isMovingRight = false;
    isShootingUp = false; isShootingDown = false; isShootingLeft = false; isShootingRight = false;


    // увеличиваем размер лабирнта
    this->n += 1;
    this->m += 1;
    // генерируем случайны лабиринт
    b = Board(screen_w * 3.f/4.f, screen_h, n, m);
    b.was.clear();
    b.dfs(0,0);

    // расчитываем размер нового персонажа
    this->human_size = static_cast<int>(screen_w / n) * 1.f/4.f;
    // создаем нового персонажа
    p = Hero(texHero, 10.f, 10.f, human_size, human_size, player_health, player_speed, player_damage);
    p.gun = Gun(texBullet, nbullets_in_player_gun, 200.f, BULLET_SPEED, 2000.f);
    
    // создаем врагов
    // расчитываем количестов врагов на уровне как максимум из измерению лабирнта
    this->num_enemy = std::max(n, m);

    // нельзя ставить врагов в ту же клетку где находится персонаж
    std::set<std::pair<int, int>> enemy_pozitions;
    enemy_pozitions.insert(std::make_pair(0, 0));
    // чистим vector enemies
    enemies.clear();
    float rand_cor_x, rand_cor_y, rand_col, rand_row;
    // инициализируем num_enemy врагов
    for (int i = 0; i < num_enemy; ++i){
        // получаем случайные координаты из поля n x m
        rand_col = (rand() % b.n);
        rand_row = (rand() % b.m);
        // пока случайные координаты не стали уникальными
        while (0 != enemy_pozitions.count(std::make_pair(rand_col, rand_row))){
            // генерируем их снова и снова
            rand_col = (rand() % b.n);
            rand_row = (rand() % b.m);
        }
        // если нашлись уникальные координаты, то запомниаем их
        enemy_pozitions.insert(std::make_pair(rand_col, rand_row));
        // и расчитываем положение врага относительно левого верзнего угла в пикселях
        rand_cor_x = rand_col * b.cell_w + b.cell_w / 2 - human_size / 2;
        rand_cor_y = rand_row * b.cell_h + b.cell_h / 2 - human_size / 2;
        // добавляем нового врга в массив врагов
        enemies.emplace_back(texEnemy, b, rand_cor_x, rand_cor_y, human_size, human_size, enemy_health, enemy_speed, enemy_damage);
        // выдаем новому врагу оружие
        enemies[i].gun = Gun(texBullet, nbullets_in_enemy_gun, 500.f, BULLET_SPEED, 2000.f);
    }
    // обновляем количество живых врагов
    enemies_alive = num_enemy;

    // увеличиваем текущий уровень
    cur_level += 1;
    // обновляем информацию о текущем уровне
    levelText.setString("Level: " + std::to_string(cur_level));

    // сбрасываем часы
    clock.restart();
}