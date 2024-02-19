#include "GameEngine.hpp"

GameEngine::GameEngine(int screen_w, int screen_h)
: window(sf::VideoMode(screen_w, screen_h), "The best game"){
	window.setFramerateLimit(60);
	b = Board(screen_w, screen_h, 25, 24);
	p = Hero(10.f, 10.f, HERO_WIDTH, HERO_HEIGHT);
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
	window.display();
}

// void GameEngine::input(void){
// 	float dx = 0, dy = 0;
// 	sf::Event event;
//     while (window.pollEvent(event)){
//         if (event.type == sf::Event::Closed)
//             window.close();
// 		if (event.type == sf::Event::KeyPressed){
//         	switch (event.key.code){
//         	case sf::Keyboard::Up:
//         		dx = 0;
//         		dy = -1;
//         		break;
//         	case sf::Keyboard::Right:
//         		dx = 1;
//         		dy = 0;
//         		break;
//         	case sf::Keyboard::Down:
//         		dx = 0;
//         		dy = 1;
//         		break;
//         	case sf::Keyboard::Left:
//         		dx = -1;
//         		dy = 0;
//         		break;
//         	}       
//         }
//         if (event.type == sf::Event::KeyReleased){
//         	switch (event.key.code){
//         	case sf::Keyboard::Up:
//         		dx = 0;
//         		dy = 0;
//         		break;
//         	case sf::Keyboard::Right:
//         		dx = 0;
//         		dy = 0;
//         		break;
//         	case sf::Keyboard::Down:
//         		dx = 0;
//         		dy = 0;
//         		break;
//         	case sf::Keyboard::Left:
//         		dx = 0;
//         		dy = 0;
//         		break;
//         	}       
//         }
//     	p.moving(b, dx, dy);
//     }
// }
void GameEngine::input(void) {
    float dx = 0, dy = 0;
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            // Set the corresponding bool variable to true when a key is pressed
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
            // Set the corresponding bool variable to false when a key is released
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

    // Calculate the dx and dy based on the bool variables
    if (isMovingUp)
        dy -= 1;
    if (isMovingRight)
        dx += 1;
    if (isMovingDown)
        dy += 1;
    if (isMovingLeft)
        dx -= 1;

    // Call your moving function with the calculated dx and dy values
    p.moving(b, dx, dy);
}