/**************************************************************************
 * Program Name:Ant.hpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	6 May 2019
 * Description: This contains the implementation for class Ant. 
 *			Ant inherits from Critter.
 *
 *		Ant has four member functions:
 *		Ant()
 *			default constructor that calls the Critter constructor that
 *			accepts two integers for the M and N coordinates respectively,
 *			a State for the critterType and a boolean for updated
 *		Ant(int, int, State, bool)
 *			constructor that accepts two integers, a State, and a boolean
 *			as arguments and passes these to the Critter constructor that
 *			accepts two integers for the M and N coordinates respectively,
 *			a State for the critterType and a boolean for updated
 *		move(Grid*)
 *			this is a virtual function that overrides the move function in
 *			Critter, it accepts a pointer to a Grid as an argument and returns
 *			nothing, it goes through the logic of an Ant's activities
 *			during a step of the simulation from eating to moving
 *		breed(Grid*, Compass)
 *			this is a virtual function that overrides the breed function in
 *			Critter, it accepts a pointer to a Grid and a Compass variable as
 *			arguments and returns nothing, it contains the logic to add a new
 *			Ant in the direction that was passed as an argument
***************************************************************************/

#include "Critter.hpp"
#include "Grid.hpp"
#include "Ant.hpp"
#include <cstdlib>

//this constructor accepts two integer variables, first for the coordM and second for the coordN
//it accepts a State variable for the critterType and a boolean for the updated variable,
//however, critterType will always be set to ant
Ant::Ant(int coordM, int coordN, State critterType, bool updated) :
	Critter(coordM, coordN, critterType, updated) {}

//move takes a pointer to a Grid object and checks for an empty space to move
//to in one direction and moves there if so. Then it increases its breedCounter
//and checks to see if it's ready to breed
void Ant::move(Grid * grid){
	//check to see if there's a place to move, if there is, move the ant there
	Compass currentDirection = findEmptyMove(grid);
	if (currentDirection != None) {
		moveTo(grid, currentDirection);
	}
	//increment breedCounter
	breedCounter++;
	//if the ant is ready to breed, then check for a viable location and 
	//attempt to breed
	if (breedCounter >= 3) {
		Compass breedDirection = findEmptyBreed(grid);
		//if there is a viable place to breed, do so
		if (breedDirection != None) {
			breed(grid, breedDirection);
			breedCounter = 0;
		}
	}
	this->updated = true;
}

//depending on the direction parameter received, use grid to add another ant
//in that direction
void Ant::breed(Grid * grid, Compass direction){
	switch (direction)	{
		case North:
			grid->addAnt(coordM - 1, coordN);
			break;
		case East:
			grid->addAnt(coordM, coordN + 1);
			break;
		case South:
			grid->addAnt(coordM + 1, coordN);
			break;
		case West:
			grid->addAnt(coordM, coordN - 1);
			break;
		default:
			break;
	}
}

bool Ant::getStarved() {
	return false;
}
