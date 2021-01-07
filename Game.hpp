/***********************************************************************************
** Program name: Group Project: Predator-Prey Game
** Author:       Yuxing Deng
** Date:         5/3/2019
** Description:  This is the header file for the Game class. It contains all of the 
** game logic and a Grid object in the game.
**
** Game consists of seven member variables:
**    steps: an integer variable that represents the number of steps to run
**    sizeM: an integer variable that represents the vertical size of the grid
**    sizeN: an integer variable that represents the horizontal size of the grid
**    numAnts: an integer variable that represents the number of ants on the grid
**    numDoodlebugs: an integer variable that represents the number of doodlbugs
**      on the grid
**    continuePlay: an boolean variable that indicates whether the user want to
**      continue playing the game.
**    grid: a pointer to the Grid object containing all the Critters
**
** Game consists of several member functions:
**    Setters for the steps, sizeM, sizeN, numAnts, numDoodlebugs and continuePlay
**    Game()
**      the default constructor that sets the steps to 0, the sizeM to 0, the 
**      sizeN to 0, the numAnts to 0, the numDoodlebugs to 0, the continuePlay
**      to false and the grid to nullptr
**    ~Game()
**	    the destructor that deallocates memory assigned to the Grid object
**    playGame()
**      this function gets all of the inputs from the user, dynamically instantiates
**      the Grid oject with the desired inputs, runs the simulation for the desired 
**      number of steps by calling playStep(). Then asks the user if they want to 
**      continue playing or exit the game. If they want to continue, it gets the 
**      additional number of steps and continues running the simulation.
**    playStep()
**      this function updates all the grid by calling grid.updateCritters()
**      and prints the current grid state by calling grid.print()    
***********************************************************************************/

#ifndef INC_162_GROUP_PROJECT_GAME_HPP
#define INC_162_GROUP_PROJECT_GAME_HPP

#include "Grid.hpp"
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include "inputValidation.hpp"
#include <iostream>

class Game 
{
private:
    int steps;                      // The number of time steps to run
    int sizeM;                      // The vertical size of the grid (rows)
    int sizeN;                      // The horizontal size of the grid (columns)
    int numAnts;                    // The number of ants
    int numDoodlebugs;              // The number of doodlebugs
    bool continuePlay;
    Grid* grid;                     // Pointer to the Grid object
	
public:
    Game();
    ~Game();

    void setSteps(int steps);
    void setSizeM(int sizeM);
    void setSizeN(int sizeN);
    void setNumAnts(int numAnts);
    void setNumDoodlebugs(int numDoodlebugs);
    void setContinuePlay(bool continuePlay);

    void playGame();
    void playStep();
};

#endif //INC_162_GROUP_PROJECT_GAME_HPP
