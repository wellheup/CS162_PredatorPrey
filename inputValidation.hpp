/***************************************************************************
** Program name: Group Project: Predator-Prey Game
** Author:  Yuxing Deng
** Date:    5/3/2019   
** Description: This is the header file for the input validation functions.
** It contains threes functions to check if the input is an integer, convert 
** the input string to integer value and check if the input is out of range.
***************************************************************************/

#ifndef INC_162_GROUP_PROJECT_INPUTVALIDATION_HPP
#define INC_162_GROUP_PROJECT_INPUTVALIDATION_HPP

#include <iostream>
#include <string>
#include <algorithm>

int getInt(int min, int max);
bool checkIfInt(std::string input);
bool checkIfOutOfRange(int input, int min, int max);

#endif //INC_162_GROUP_PROJECT_INPUTVALIDATION_HPP
