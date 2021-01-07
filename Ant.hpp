/**************************************************************************
 * Program Name:Ant.hpp
 * Name:	Manda Jensen & Phillip Wellheuser
 * Date:	6 May 2019
 * Description: This contains the header file for class Ant. 
 *			Ant inherits from Critter.
 * 
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

#ifndef ANT_H
#define ANT_H

class Grid;
enum Compass; 

class Ant : public Critter{
	private:
		
	public:
		Ant(int coordM, int coordN, State critterType, bool updated);
		void move(Grid* grid);
		void breed(Grid* grid, Compass direction);
		bool getStarved();
};

#endif //ANT_H