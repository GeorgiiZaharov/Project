#include <iostream>
#include <random>
#include <ctime>
#include "GameEngine.hpp"


int main(){
	srand(time(NULL));
    GameEngine ge(800, 600);
    ge.run();
}