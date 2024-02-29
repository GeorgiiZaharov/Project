#include <iostream>
#include <random>
#include <ctime>
#include "GameEngine.hpp"


int main(){
	srand(time(NULL));
    GameEngine ge;
    ge.run();
}