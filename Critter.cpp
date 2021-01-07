/**************************************************************************
 * Program Name:Critter.cpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	30 APR 2019
 * Description: This contains the header file for class Critter and has a circular
 * 		dependancy with class Grid.
 *		Critter defines one enum:
 *		Compass		5 states that represent the cardinal directions and 
 *				None if no cardinal direction is warranted
 *		Critter consists of four member variables:
 *		critterType	a state variable that describes the subclass that
 *				the critter belongs to (ant or doodlebug)
 *		coordM		an integer variable that represents the vertical
 *				coordinate of the critter's current position
 *		coordN		an integer variable that represents the horizontal
 *				coordinate of the critter's current position
 *		breedCounter	an integer variable that represents the number of
 *				steps that have passed since the critter last bred
 *		updated		a boolean variable that represents whether or not the
 *				critter has been updated during the current step
 *
 *		Critter consists of several member functions:
 *		Critter()	
 *			the default constructor that sets the critterType to
 *			none, the coordM and coordN to 0, the breedCounter to 0
 *			and updated to false
 *		Critter(int, int, State, bool)
 *			the constructor that accepts two integer variables, first
 *			for the coordM and second one for the coordN, a State 
 *			variable for the critterType, and a boolean for updated
 *		getType()
 *			this function takes no arguments and returns a State variable
 *			that represents the Critter's critterType variable
 *		getUpdated()
 *			this function takes no arguments and returns a boolean variable that
 *			represents the current state of the Critter's updated variable
 *		move(Grid*) - not defined here since it is purely virtual
 *			this is a purely virtual function that takes a pointer to a Grid
 *			object as an argument and returns nothing, this is overriden in
 *			the Ant and Doodlebug classes and contains logic for the Critter's
 *			activities during one step of the simulation
 *		breed(Grid*, Compass) - not defined here since it is purely virtual
 *			this is a purely virtual function that takes a pointer to a Grid
 *			object and a Compass variable and returns nothing, this is overriden
 *			in the Ant and Doodlebug classes and contains the logic to add a new
 *			Critter of the type that calls it in the direction that was passed as
 *			an argument
 *		getRandomDirection()
 *			this function takes no arguments and returns a Compass variable, it
 *			randomly chooses a direction of the Compass enum and returns it
 *		moveTo(Grid*, Compass)
 *			this function takes a pointer to a Grid object and a Compass variable
 *			as arguments and returns nothing, it moves the Critter that is calling it 
 *			one placement over in the grid that is passed as directed by the passed 
 *			Compass variable and updates the Critter's coordinates to the new location
 * 		shiftCoords(int&, int&, Compass)
 *			this function takes two integers by reference representing the M and N
 *			coordinates of a location and a Compass variable representing the direction
 *			those coordinates should be shifted and the function changes the coordinates
 *			in the specificed direction, this function returns nothing
 *		getNeighbor(Grid*, Compass)
 *			this function takes a pointer to a Grid object and a Compass variable and
 *			it returns a State variable, it returns the critterType of the adjacent Critter
 *			in the direction specified by the Compass enum
 *		findEmptyMove(Grid*)
 *			this function takes a pointer to a Grid object and returns a Compass variable
 *			it randomly chooses a direction then checks the state of the square that is
 *			the random direction from the calling Critter, if the square is empty it returns
 *			the direction that was checked, if not then it returns None
 *		findEmptyBreed(Grid*)
 *			this function takes a pointer to a Grid object and returns a Compass variable
 *			it first checks if there is an empty square adjacent to the calling Critter, if
 *			not then it returns none, if so then it randomly chooses a direction and checks if
 *			that square is empty until it finds an empty square and returns the direction that
 *			the empty square is in
 *		reset()
 *			this function takes no arguments and returns nothing, it sets the updated
 *			flag to false
************************************************************************************************/

#include "Critter.hpp"
#include "Grid.hpp"

#include <cstdlib>

//the default constructor that sets the critterType to none, the coordM and coordN to 0 and the 
//breedCounter to 0 and updated to false
Critter::Critter()
{	this->critterType = empty;
	this->coordM = 0;
	this->coordN = 0;
	this->breedCounter = 0;
	this->updated = false;
}


//this constructor accepts two integer variables, first for the coordM and second for the coordN
//it accepts a State variable for the critterType and a boolean for the updated variable
Critter::Critter(int coordM, int coordN, State critterType, bool updated)
{	this->critterType = critterType;
	this->coordM = coordM;
	this->coordN = coordN;
	this->breedCounter = 0;
	this->updated = updated;
}

//this function takes no arguments and returns a State that is the critterType of the Critter
State Critter::getType()
{	return this->critterType;
}

//getUpdated takes no arguments and returns a boolean that is the updated boolean of Critter
bool Critter::getUpdated()
{	return this->updated;
}

//getRandomDirection takes no arguments and returns a Compass variable, it randomly chooses
//a direction and returns it
Compass Critter::getRandomDirection()
{	//use rand() to return an integer between 0 and 3 to represent a cardinal direction
	return static_cast<Compass>(rand()%4);
}

//moveTo takes a pointer to a Grid object and a Compass variable as arguments and returns nothing, it
//moves the Critter that calls this function one placement over in the grid in the direction passed
//and updates the Critter's coordinates to the new location, moveTo will only move the critter if the
//state of the destination space is empty
void Critter::moveTo(Grid* grid, Compass direction)
{	//first check if the destination cell is empty	
	if(getNeighbor(grid, direction) == empty)
	{	//if so, inialize two int variables to hold the new destination and call shiftCoords
		//to change the destination coordinates as the direction argument calls for	
		int destM = coordM;
		int destN = coordN;
		shiftCoords(destM, destN, direction);
		
		//changes the location of the critter to the destination coordinates by calling
		//moveCritter on the grid pointer object and passing the new and old coordinates
		grid->moveCritter(coordM, coordN, destM, destN);

		//set the coordinates of the critter to the new location now that it has been moved
		coordM = destM;
		coordN = destN;
	}
}

//shiftCoords takes two integers by refrence represeting the M and N coordinates of a location and
//a Compass variable representing the direction to shift those coordinates to represent, the function
//changes the coordinates in the direction specified and returns nothing
void Critter::shiftCoords(int& destM, int& destN, Compass direction)
{	//use a switch statement based on the direction passed as an argument to change the 
	//appropriate destination coordinate to point to the space in the direction passed
	switch(direction)
	{	case North:
			destM--;
			break;
		case East:
			destN++;
			break;
		case South:
			destM++;
			break;
		case West:
			destN--;
			break;
		default:
			break;
	}
}

//getNeighbor takes a pointer to a Grid object and a Compass variable and returns a State variable, the
//returned State variable represents the state of the adjacent space on the grid in the direction
//passed as an argument, this function uses the getSquareState of the Grid object
State Critter::getNeighbor(Grid* grid, Compass direction)
{	//use a switch statement based on the direction passed as an argument to call the
	//grid pointer's getSquareState function with the coordinates for that direction from the 
	//calling Critter's position
	switch(direction)
	{	case North:
			return grid->getSquareState(coordM-1, coordN);			
		case East:
			return grid->getSquareState(coordM,coordN+1);
		case South:
			return grid->getSquareState(coordM+1,coordN);
		case West:
			return grid->getSquareState(coordM,coordN-1);
		default:
			break;
	}
	//in the case that an invalid direction was passed, return offGrid
	return offGrid;
}

//findEmptyMove takes a pointer to a Grid object and returns a Compass variable it randomly chooses 
//a direction then checks the state of the square that is the random direction from the calling Critter, 
//if the square is empty it returns the direction that was checked, if not then it returns None
Compass Critter::findEmptyMove(Grid* grid)
{	//declare a Compass variable and set it equal to a random direction
	Compass moveDirection = getRandomDirection();
	//check the state of the square in that direction, if it is empty then return
	//the direction of the empty square, if not return None
	if(getNeighbor(grid, moveDirection) == empty)
	{	return moveDirection;
	}
	else
	{	return None;
	}
}
 

//findEmptyBreed takes a pointer to a Grid object and returns a Compass variable it first checks if 
//there is an empty square adjacent to the calling Critter, if not then it returns none, if so then 
//it randomly chooses a direction and checks if that square is empty until it finds an empty square 
//and returns the direction that the empty square is in
Compass Critter::findEmptyBreed(Grid* grid)
{	//check if there are any empty squares adjacent to the critter calling the function
	if(getNeighbor(grid, North) == empty || getNeighbor(grid, East) == empty || 
		getNeighbor(grid, South) == empty || getNeighbor(grid, West) == empty) 

	{	//if there is an empty square adjacent to the critter calling the function
		//then initalize a Compass variable to check the state of the square 
		//and a State variable to hold the state of the square being checked
		Compass breedDirection = None;
		State neighborState = offGrid;

		//randomly choose a direction and check if it is empty until finding an empty neighbor
		do
		{	breedDirection = getRandomDirection();
			neighborState = getNeighbor(grid, breedDirection);
		}while(neighborState != empty);

		//return the direction of a square that is empty
		return breedDirection;
	}

	//if there are no empty squares adjacent to the critter calling the function then return
	//the direction None
	else
	{	return None;
	}
}	

//the reset function takes no arguments and returns nothing, it sets the updated flag to false
void Critter::reset()
{	this->updated = false;
}

