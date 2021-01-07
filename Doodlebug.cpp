/**************************************************************************
 * Program Name:Doodlebug.hpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	6 May 2019
 * Description: This contains the implementation for class Doodlebug.
 *		Doodlebug inherits from Critter. Doodlebug defines one additional
 *		member variable:
 *		starveCounter	an integer variable that represents the number of
 *				steps that have passed since the Doodlebug last ate
 *
 *		Doodlebug has five member functions:
 *		Doodlebug()
 *			default constructor that calls the Critter constructor that
 *			accepts two integers for the M and N coordinates respectively,
 *			a State for the critterType and a boolean for updated
 *		Doodlebug(int, int, State, bool)
 *			constructor that accepts two integers, a State, and a boolean
 *			as arguments and passes these to the Critter constructor that
 *			accepts two integers for the M and N coordinates respectively,
 *			a State for the critterType and a boolean for updated
 *		move(Grid*)
 *			this is a virtual function that overrides the move function in
 *			Critter, it accepts a pointer to a Grid as an argument and returns
 *			nothing, it goes through the logic of a Doodlebug's activities
 *			during a step of the simulation, starting with eating, then moving,
 *			and finally dying and/or breeding
 *		breed(Grid*, Compass)
 *			this is a virtual function that overrides the breed function in
 *			Critter, it accepts a pointer to a Grid and a Compass variable as
 *			arguments and returns nothing, it contains the logic to add a new
 *			Doodlebug in the direction that was passed as an argument
 *		eat(Grid*)
 *			function that takes a pointer to a Grid as an argument and returns
 *			a boolean, it determines if there is anything that can be eaten around
 *			the doodlebug and if so, eats it and takes it's spot and returns true,
 *			if not, it returns false
***************************************************************************/

#include "Critter.hpp"
#include "Grid.hpp"
#include "Doodlebug.hpp"
#include <cstdlib>

//this constructor accepts two integer variables, first for the coordM and second for the coordN
//it accepts a State variable for the critterType and a boolean for the updated variable,
//however, critterType will always be set to doodlebug
Doodlebug::Doodlebug(int coordM, int coordN, State critterType, bool updated) :
	Critter(coordM, coordN, critterType, updated) {
	this->starveCounter = 0;
	this->starved = false; 
}

//move takes a pointer to a Grid object and checks for an empty space to move
//to in one direction and moves there if so. Then it increases its breedCounter
//and checks to see if it's ready to breed
void Doodlebug::move(Grid * grid)
{	
	Compass currentDirection = findEmptyMove(grid);
	//attempts to eat instead of a normal move action first, if it eats successfully
	//the starve Counter is reset to 0
	if (eat(grid) == true) {
		starveCounter = 0;
	}
	//if the doodlebug doesn't eat, it moves like an ant and then increments starveCounter
	else {
		if (currentDirection != None) {
			moveTo(grid, currentDirection);
		}
		starveCounter++;
	}
	//increment breedCounter
	breedCounter++;
	//if the doodlebug is ready to breed, then check for a viable location and breed
	if (this->breedCounter >= 8) {
		Compass breedDirection = findEmptyBreed(grid);
		//if there is a viable place to breed, do so
		if (breedDirection != None) {
			breed(grid, breedDirection);
			breedCounter = 0;
		}
	}
	//if the doodlebug is ready to starve, then use the grid to destroy this doodlebug
	if (this->starveCounter >= 3) {
		this->starved = true;
	}
	this->updated = true;
}

//depending on the direction parameter received, use grid to add another doodlebug
//in that direction
void Doodlebug::breed(Grid * grid, Compass direction){	
	switch (direction){
		case North:
			grid->addDoodlebug(coordM - 1, coordN);
			break;
		case East:
			grid->addDoodlebug(coordM, coordN + 1);
			break;
		case South:
			grid->addDoodlebug(coordM + 1, coordN);
			break;
		case West:
			grid->addDoodlebug(coordM, coordN - 1);
			break;
		default:
			break;
	}
}

//eat takes a pointer to a Grid object and returns a bool it first checks if 
//there are any ants adjacent to the calling doodlebug, if not, then it returns 
//false, if so then it randomly chooses a direction and checks for ants until
//it finds one and returns the direction that the ant is in
bool Doodlebug::eat(Grid * grid){	
	if (getNeighbor(grid, North) == ant || getNeighbor(grid, East) == ant ||
		getNeighbor(grid, South) == ant || getNeighbor(grid, West) == ant){	
		//if there is an ant adjacent to the doodlebug calling the function
		//then initalize a Compass variable to check the state of the square 
		//and a State variable to hold the state of the square being checked
		Compass antDirection = None;
		State neighborState = offGrid;

		//randomly choose a direction and check if it has an ant until finding an ant neighbor
		do{
			antDirection = getRandomDirection();
			neighborState = getNeighbor(grid, antDirection);
		} while (neighborState != ant);

		//eat one of the found ants
		switch (antDirection){
			case North:
				grid->deleteCritter(coordM - 1, coordN);
				break;
			case East:
				grid->deleteCritter(coordM, coordN + 1);
				break;
			case South:
				grid->deleteCritter(coordM + 1, coordN);
				break;
			case West:
				grid->deleteCritter(coordM, coordN - 1);
				break;
			default:
				break;
		}
		//move to that ant's square
		moveTo(grid, antDirection);

		//return true, that the doodlebug has eaten
		return true;
	}
	//if there are no ants adjacent to the doodlebug calling the function then return
	//the direction None
	else{
		return false;
	}
}

bool Doodlebug::getStarved(){
	return this->starved;
}
