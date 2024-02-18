#include <iostream>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main(){
	srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Board b(800, 600, 20, 20);
	b.dfs(0,0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        b.draw(window);
        window.display();
    }
}