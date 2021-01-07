/*****************************************************************************
** Program name: Group Project: Predator-Prey Game
** Author:       Yuxing Deng
** Date:         5/3/2019
** Description:  This is the implementation file for the Game class. 
** It contains all of the game logic and a Grid object in the game.
*****************************************************************************/
#include "Game.hpp"

using std::cout;
using std::cin;
using std::endl;


/*****************************************************************************
** Function:    Game()
** Description: Default constructor for the Game class
**              It sets the steps to 0, the sizeM to 0, the sizeN to 0, the 
**              numAnts to 0, the numDoodlebugs to 0, the continuePlay to false 
**              and the grid to nullptr
** Called by:   main function
*****************************************************************************/
Game::Game()
{
    this->steps = 0;
    this->sizeM = 0;                     
    this->sizeN = 0;                     
    this->numAnts = 0;                   
    this->numDoodlebugs = 0;             
    this->continuePlay = false;
    this->grid = nullptr;
}


/****************************************************************************
** Function:    ~Game()
** Description: Destructor for the Game class.
**              Deallocates memory assigned to the Grid object
****************************************************************************/
Game::~Game()
{
    delete grid;
}


/****************************************************************************
** Function:    setSteps()
** Description: It takes an integer as parameter and passes it to 
**              data memeber steps
****************************************************************************/
void Game::setSteps(int steps)
{
    this->steps = steps;
}


/****************************************************************************
** Function:    setSizeM()
** Description: It takes an integer as parameter and passes it to
**              data memeber sizeM
****************************************************************************/
void Game::setSizeM(int sizeM)
{
    this->sizeM = sizeM;
}


/****************************************************************************
** Function:    setSizeN()
** Description: It takes an integer as parameter and passes it to
**              data memeber sizeN
****************************************************************************/
void Game::setSizeN(int sizeN)
{
    this->sizeN = sizeN;
}


/****************************************************************************
** Function:    setNumAnts()
** Description: It takes an integer as parameter and passes it to
**              data memeber numAnts
****************************************************************************/
void Game::setNumAnts(int numAnts)
{
    this->numAnts = numAnts;
}


/****************************************************************************
** Function:    setNumDoodlebugs()
** Description: It takes an integer as parameter and passes it to
**              data memeber numDoodlebugs
****************************************************************************/
void Game::setNumDoodlebugs(int numDoodlebugs)
{
    this->numDoodlebugs = numDoodlebugs;
}


/****************************************************************************
** Function:    setContinuePlay()
** Description: It takes an integer as parameter and passes it to
**              data memeber continuePlay
****************************************************************************/
void Game::setContinuePlay(bool continuePlay)
{
    this->continuePlay = continuePlay;
}


/*****************************************************************************
** Function:    playGame()
** Description: Gets all of the inputs from the user, dynamically instantiates
**              a Grid oject with the desired inputs, runs the simulation for
**              the desired number of steps by calling playStep(). Then asks the
**              user if they want to continue or exit the game. If they want 
**              continue gets the additional number of steps and continues 
**              running the simulation.
*****************************************************************************/
void Game::playGame()
{
    cout << "-- Welcome to Predator-Prey Game --" << endl;
    cout << "We did extra credit!" << endl;

    // Prompt the user for the sizeM and sizeN of the grid, the number of doodlebugs and
    // the number of ants, then verify all the inputs and assign them to data members.
    cout << "Please enter the rows of the grid (max: 80):" << endl;
    int sizeMIn = getInt(1, 80);
    setSizeM(sizeMIn);

    cout << "Please enter the columns of the grid (max: 80):" << endl;
    int sizeNIn = getInt(1, 80);
    setSizeN(sizeNIn);

    cout << "Please enter the number of doodlebugs on the grid:" << endl;
    int numDoodlebugsIn = getInt(1, sizeM * sizeN - 1);
    setNumDoodlebugs(numDoodlebugsIn);

    cout << "Please enter the number of ants on the grid:" << endl;
    int numAntsIn = getInt(1, sizeM * sizeN - numDoodlebugs);
    setNumAnts(numAntsIn);
	
    grid = new Grid(sizeM, sizeN, numAnts, numDoodlebugs);

    do
    {
        // Prompt the user for the number of steps to run,
        // then verify and assign the input to data member steps
        cout << "Please enter the number of steps to run:" << endl;
        int stepsIn = getInt(1, 1000);
        setSteps(stepsIn);

        for (int i = 0; i < steps; i++)
        {
            playStep();
        }

        cout << "1.Continue Playing;  2.Exit the Game" << endl;
        cout << "Please enter 1 or 2:" << endl;
        int keepPlaying = getInt(1, 2);
		
        if (keepPlaying == 1)
        {
            setContinuePlay(true);
        }
        else
        {
            setContinuePlay(false);
        }

    } while (continuePlay);
}


/*****************************************************************************
** Function:    playStep()
** Description: This function updates all the grid by calling 
**              grid.updateCritters() and prints the current grid state 
**              by calling grid.print()
** Called by:   playGame()
*****************************************************************************/
void Game::playStep()
{
    grid->updateCritters();
    grid->print();
}
