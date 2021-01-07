/**************************************************************************
 * Program Name:Doodlebug.hpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	6 May 2019
 * Description: This contains the header file for class Doodlebug. 
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
 *			and finally dying or breeding 
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

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

class Grid;
enum Compass;

class Doodlebug : public Critter{
private:
	int starveCounter;
	bool starved; 
public:
	Doodlebug(int coordM, int coordN, State critterType, bool updated);
	void move(Grid* grid);
	void breed(Grid* grid, Compass direction);
	bool eat(Grid* grid);
	bool getStarved();
};

#endif //DOODLEBUG_H
