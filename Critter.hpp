/**************************************************************************
 * Program Name:Critter.hpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	29 APR 2019
 * Description: This contains the header file for class Critter and has a circular
 * 		dependancy with class Grid.
 *		Critter header file defines one enum:
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
 *			this function takes no arguments and returns a bool variable
 *			that represents the current status of the Critter's updated variable 
 *		getStarved()
 *			this is a purely virtual function that takes no arguments and
 *			returns a bool, the starved bool of the Doodlebug Critter, it needs
 *			to be defined here so that it can be called from a Critter pointer
 *		move(Grid*)
 *			this is a purely virtual function that takes a pointer to a Grid
 *			object as an argument and returns nothing, this is overriden in
 *			the Ant and Doodlebug classes and contains logic for the Critter's
 *			activities during one step of the simulation
 *		breed(Grid*, Compass)		
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
 *		~Critter()
 *			this is a virtual destructor since this is an abstract class, the destructor
 *			is set to the default constructor
************************************************************************************************/

#ifndef CRITTER_H
#define CRITTER_H

//include the file that has the definition of the State enum
#include "State.hpp"

//forward declaration of Grid because of circular dependancy between Critter and Grid
class Grid;	

//definition of the Compass enum used in Critter
enum Compass{North = 0, East = 1, South = 2, West = 3, None = 4};

class Critter
{
	protected:
		State critterType;
		int coordM;
		int coordN;
		int breedCounter;
		bool updated;

	public:
		Critter();
		Critter(int coordM, int coordN, State critterType, bool updated);
		State getType();
		bool getUpdated();
		virtual bool getStarved() = 0;
		virtual void move(Grid*) = 0;
		virtual void breed(Grid* grid, Compass direction) = 0;
		Compass getRandomDirection();
		void moveTo(Grid* grid, Compass direction);
		void shiftCoords(int& destM, int& destN, Compass direction);
 		State getNeighbor(Grid* grid, Compass direction);
		Compass findEmptyMove(Grid* grid);
		Compass findEmptyBreed(Grid* grid);
 		void reset();
		virtual ~Critter() = default;
};

#endif //CRITTER_H
