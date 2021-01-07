/******************************************************************************
**  Program name:  Grid.hpp
**  Author:        Derth Adams
**  Date:          May 12, 2019
**  Description:   Header file for the Grid class. Represents the grid in the
**                 Ant/Doodlebug simulation. Contains functions for moving,
**                 adding, deleting, and updating Ant/Doodlebugs as well as
**                 printing the grid.
*******************************************************************************/

#ifndef INC_162_GROUP_PROJECT_GRID_HPP
#define INC_162_GROUP_PROJECT_GRID_HPP
#include "State.hpp"

class Doodlebug;

class Critter;  // Forward declaration of Critter because of circular
                // dependency between Critter and Grid
class Grid
{
private:
    int sizeM;                      // The vertical size of the grid (rows)
    int sizeN;                      // The horizontal size of the grid (columns)
    Critter*** array = nullptr;     // 2D array of pointers to Critter
                                    // representing the grid
public:

    Grid(int sizeM, int sizeN, int numAnts, int numDoodlebugs);
    ~Grid();
    bool moveCritter(int originM, int originN, int destM, int destN);
    bool addAnt(int coordM, int coordN);
    bool addDoodlebug(int coordM, int coordN);
    bool deleteCritter(int coordM, int coordN);
    void resetCritters();
    void updateCritters();
    int getSizeM();
    int getSizeN();
    void print();
    State getSquareState(int coordM, int coordN);
};

#endif //INC_162_GROUP_PROJECT_GRID_HPP
