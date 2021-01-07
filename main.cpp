/********************************************************************************
** Program name: Group Project: Predator-Prey Game
** Author:       Yuxing Deng
** Date:         5/3/2019
** Description:  This program simulates a 2D predator-prey game. The preys are 
**               ants and the predators are doodlebugs. It contains an Ant class
**               and a Doodlebug class that both inherits the behavior and elements 
**               of a Critter class. It has a Grid class that contains a pointer
**               to a 2D array which represents the grid. The Grid class has several
**               member functions to add ants and doodlebugs onto the grid, update
**               the critters in every step and print the grid. The program also
**               has a Game class which contains all of the game logic.
********************************************************************************/
#include "Game.hpp"
#include <ctime>

int main()
{
    unsigned seed;
    seed = time(0);
    srand(seed);

    Game* game = new Game();
    game->playGame();

    delete game;

    return 0;
}
