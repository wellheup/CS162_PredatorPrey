/******************************************************************************
**  Program name:  Grid.cpp
**  Author:        Derth Adams
**  Date:          May 12, 2019
**  Description:   Implementation file for the Grid class. Represents the grid
**                 in the Ant/Doodlebug simulation. Contains functions for
**                 moving, adding, deleting, and updating Ant/Doodlebugs as
**                 well as printing the grid.
*******************************************************************************/

#include <iostream>
#include "Grid.hpp"
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"

/*******************************************************************************
**  Function name:  Grid(int, int, int, int)
**  Description:    Constructor for the Grid class. Allocates a 2D array of
**                  pointers to Critter and sets them to nullptr, then randomly
**                  populates the grid with the desired number of Ant and
**                  Doodlebug objects.
**  Inputs:         Four ints:
**                  The first two represent the vertical and horizontal size
**                  of the grid
**                  The third is the starting number of Ants
**                  The fourth is the starting number of Doodlebugs
**  Called by:      Game
*******************************************************************************/

Grid::Grid(int sizeM, int sizeN, int numAnts, int numDoodlebugs)
{
    this->sizeM = sizeM;
    this->sizeN = sizeN;
    array = new Critter**[sizeM];
    for (int i = 0; i < sizeM; i++)
    {
        array[i] = new Critter*[sizeN];
        for (int j = 0; j < sizeN; j++)
        {
            array[i][j] = nullptr;
        }
    }

    int randM;
    int randN;
    bool critterPlaced;
    for (int i = 0; i < numAnts; i++)
    {
        critterPlaced = false;
        while (!critterPlaced)
        {
            randM = rand() % sizeM;
            randN = rand() % sizeN;
            critterPlaced = addAnt(randM, randN);
        }
    }
    for (int i = 0; i < numDoodlebugs; i++)
    {
        critterPlaced = false;
        while (!critterPlaced)
        {
            randM = rand() % sizeM;
            randN = rand() % sizeN;
            critterPlaced = addDoodlebug(randM, randN);
        }
    }
}

/*******************************************************************************
**  Function:       ~Grid()
**  Description:    Destructor for the Grid class. Deallocates memory
**                  assigned to array.
*******************************************************************************/

Grid::~Grid()
{
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j])
            {
                delete array[i][j];
                array[i][j] = nullptr;
            }
        }
        delete[] array[i];
        array[i] = nullptr;
    }
    delete[] array;
    array = nullptr;
}

/******************************************************************************
**  Function:       bool moveCritter(int, int, int, int)
**  Description:    Moves an Ant/Doodlebug from one square to another.
**                  Does bounds checking on all inputs, checks to see
**                  if the destination is clear, copies the origin
**                  pointer to the destination pointer, sets the origin
**                  pointer to nullptr.
**  Inputs:         Four ints:
**                  First two are the (m, n) coordinates of the object to be
**                  moved, second two are the (m, n) coordinates of the
**                  object's destination.
**  Outputs:        True if the object was successfully moved.
**                  False if the destination was occupied by another
**                  object or if any of the input coordinates were
**                  off the grid.
**  Called by:      Ant, Doodlebug
******************************************************************************/

bool Grid::moveCritter(int originM, int originN, int destM, int destN)
{
    // Bounds-checking on input coordinates
    if ((originM >= 0 && originM < sizeM) &&
        (originN >= 0 && originN < sizeN) &&
        (destM >= 0 && destM < sizeM) &&
        (destN >= 0 && destN < sizeN))
    {
        // If there's a critter at the origin and destination is empty
        if (array[originM][originN] && !array[destM][destN])
        {
            // Move critter to destination and return true
            array[destM][destN] = array[originM][originN];
            array[originM][originN] = nullptr;
            return true;
        }
    }
    // If coordinates out of bounds, no critter at origin, or destination
    // occupied return false
    return false;
}

/******************************************************************************
**  Function:       bool addAnt(int, int)
**  Description:    Adds a new Ant to the grid.
**                  Does bounds checking on all inputs, checks to see
**                  if the square at the coordinates is clear,
**                  dynamically instantiates a new Ant object in the
**                  square at the coordinates.
**  Inputs:         Two ints representing the (m, n) coordinates where the
**                  new Ant object should be placed on the grid.
**  Outputs:        True if the new Ant was successfully placed.
**                  False if the destination was occupied by another
**                  object or if any of the input coordinates were
**                  off the grid.
**  Called by:      Grid, Ant
*******************************************************************************/

bool Grid::addAnt(int coordM, int coordN)
{
    // Bounds-checking on input coordinates
    if ((coordM >=0 && coordM < sizeM) &&
        (coordN >=0 && coordN < sizeN))
    {
        // If the square at the input coordinates is empty
        if (!array[coordM][coordN])
        {
            // Add an ant and return true
            array[coordM][coordN] = new Ant(coordM, coordN, ant, false);
            return true;
        }
    }
    // If coordinates are out of bounds or square is occupied, return false
    return false;
}

/******************************************************************************
**  Function:       bool addDoodlebug(int, int)
**  Description:    Adds a new Doodlebug to the grid.
**                  Does bounds checking on all inputs, checks to see
**                  if the square at the coordinates is clear,
**                  dynamically instantiates a new Doodlebug object in the
**                  square at the coordinates.
**  Inputs:         Two ints representing the (m, n) coordinates where the
**                  new Doodlebug object should be placed on the grid.
**  Outputs:        True if the new Doodlebug was successfully placed.
**                  False if the destination was occupied by another
**                  object or if any of the input coordinates were
**                  off the grid.
**  Called by:      Grid, Doodlebug
*******************************************************************************/

bool Grid::addDoodlebug(int coordM, int coordN)
{
    // Bounds-checking on input coordinates
    if ((coordM >=0 && coordM < sizeM) &&
        (coordN >=0 && coordN < sizeN))
    {
        // If the square at the input coordinates is empty
        if (!array[coordM][coordN])
        {
            // Add a doodlebug and return true
            array[coordM][coordN] =
                    new Doodlebug(coordM, coordN, doodlebug, false);
            return true;
        }
    }
    // If coordinates are out of bounds or square is occupied, return false
    return false;
}

/******************************************************************************
**  Function:       bool deleteCritter(int, int)
**  Description:    Deletes an Ant or Doodlebug from the grid.
**                  Does bounds checking on inputs, checks to see
**                  if the square at the coordinates contains an object,
**                  deletes the object and sets the pointer to nullptr.
**  Inputs:         Two ints representing the (m, n) coordinates of the
**                  Ant or Doodlebug object to be deleted.
**  Outputs:        True if the object was successfully deleted.
**                  False if the specified square was empty or if any
**                  of the input coordinates were off the grid.
**  Called by:      Grid, Doodlebug
*******************************************************************************/

bool Grid::deleteCritter(int coordM, int coordN)
{
    // Bounds-checking on input coordinates
    if ((coordM >=0 && coordM < sizeM) &&
        (coordN >=0 && coordN < sizeN))
    {
        // If the square at the input coordinates is occupied
        if (array[coordM][coordN])
        {
            // Delete the ant/doodlebug and return true
            delete array[coordM][coordN];
            array[coordM][coordN] = nullptr;
            return true;
        }
    }
    // If coordinates are out of bounds or square is occupied, return false
    return false;

}

/******************************************************************************
**  Function:       void resetCritters()
**  Description:    Resets the flags of all Ants and Doodlebugs on the
**                  grid by calling their reset() functions.
**  Called by:      Grid
*******************************************************************************/

void Grid::resetCritters()
{
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j])
            {
                array[i][j]->reset();
            }
        }
    }
}

/******************************************************************************
**  Function:       void updateCritters()
**  Description:    Updates all Ants and Doodlebugs in the grid.
**                  First it resets the flags of all Ants and Doodlebugs.
**                  Then it does three passes through all the squares
**                  on the grid:
**                  1. For each Doodlebug, if the "updated" flag is
**                  false, it calls the Doodlebug's move() function.
**                  2. For each Doodlebug, if the "starved" flag is set,
**                  then it is deleted.
**                  3. For each Ant, if the "updated" flag is false,
**                  it calls the Ant's move() function.
**  Called by:      Game
*******************************************************************************/

void Grid::updateCritters()
{
    resetCritters();
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j] && array[i][j]->getType() == doodlebug)
            {
                if (!array[i][j]->getUpdated())
                {
                    array[i][j]->move(this);
                }
            }
        }
    }
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j] && array[i][j]->getType() == doodlebug)
            {
                if (array[i][j]->getStarved())
                {
                    deleteCritter(i, j);
                }
            }
        }
    }
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j] && array[i][j]->getType() == ant)
            {
                if (!array[i][j]->getUpdated())
                {
                    array[i][j]->move(this);
                }
            }
        }
    }
}

// Getter for the vertical size of the grid

int Grid::getSizeM()
{
    return sizeM;
}

// Getter for the horizontal size of the grid
int Grid::getSizeN()
{
    return sizeN;
}

/******************************************************************************
**  Function:       void print()
**  Description:    Prints out the current state of the grid using
**                  an "X" for Doodlebugs, "O" for Ants, and a blank
**                  space for unoccupied squares.
**  Called by:      Game
*******************************************************************************/

void Grid::print()
{
    for (int i = 0; i < sizeN * 2 + 3; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
    for (int i = 0; i < sizeM; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < sizeN; j++)
        {
            if (array[i][j])
            {
                if (array[i][j]->getType() == ant)
                {
                    std::cout << "O ";
                }
                if (array[i][j]->getType() == doodlebug)
                {
                    std::cout << "X ";
                }
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << '|';
        std::cout << std::endl;
    }
    for (int i = 0; i < sizeN * 2 + 3; i++)
    {
        std::cout << '-';
    }
    std::cout << std::endl;
}

/******************************************************************************
**  Function:       int getSquareState(int coordM, int coordN)
**  Description:    Returns the state of a specific square on the board.
**  Inputs:         Two ints representing the (m, n) coordinates of the
**                  square that the Ant/Doodlebug wants to know the
**                  state of.
**  Outputs:        **Needs to be decided how the state will be coded**
**  Called by:      Ant, Doodlebug
*******************************************************************************/

State Grid::getSquareState(int coordM, int coordN)
{
    if ((coordM < 0 || coordM >= sizeM) ||
        (coordN < 0 || coordN >= sizeN))
    {
        return offGrid;
    }
    if (array[coordM][coordN])
    {
        return array[coordM][coordN]->getType();
    }
    else
    {
        return empty;
    }
}