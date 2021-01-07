/***************************************************************************
** Program name: Group Project: Predator-Prey Game
** Author:  Yuxing Deng
** Date:    5/3/2019
** Description:  This is the implementation file for the input validation 
** functions. It contains threes functions to check if the input is an
** integer, convert the input string to integer value and check if the input
** is out of range.
***************************************************************************/

#include "inputValidation.hpp"

/***************************************************************************
** Function name: getInt    
** Description: This function has two parameters: a low limit and a high limit 
** for an input integer. It prompts the user for an integer and keeps checking
** if the input is an integer within the limits that were passed as arguments
** until the user enters a qualified integer. Then it returns the number.
***************************************************************************/
int getInt(int min, int max)
{
    std::string input;
    int num;
  
    do
    {
        // Temporarily hold user input
        getline(std::cin, input);
    
        if (!checkIfInt(input))
        {
            std::cout << "That input is invalid! " 
            << "Please enter an integer:" << std::endl;
        }
     
    } while (!checkIfInt(input));

    num = atoi(input.c_str());

    while (checkIfOutOfRange(num, min, max))
    {
        std::cout << "Please enter an integer between " 
        << min << " and " << max << std::endl;

        num = getInt(min, max);
    }
    
 
    return num;    
} 


/***************************************************************************
** Function name: checkIfInt    
** Description: This function takes a string as parameter. Then it checks
** every character of the string to see if they are digit (the first character
** could be '+' or '-'. If so. it turns true, otherwise, it returns false.
***************************************************************************/
bool checkIfInt(std::string input)
{
    int length = input.size();

    if (length <= 1)
    {
        if (!isdigit(input[0]))
        {
            return false;
        }
    }
    else
    {

        for (int i = 0; i < length; i++)
        {
            if (i > 0)
            {
                if (!isdigit(input[i]))
                {
                    return false;
                }
            }
            // The first character can have a + or - indicating the sign of the integer
            // Check for that only on the first character of the input
            else
            {
                if (!isdigit(input[i]) && input[i] != '-' && input[i] != '+')
                {
                    return false;
                }
            }
        }
    }

    return true;
}

/***************************************************************************
** Function name: checkIfOutOfRange
** Description: This function takes threes int variables: input, min and max
** as parameters. If the input is out of range between the min and max, it
** returns true. Otherwise, it returns false.
***************************************************************************/
bool checkIfOutOfRange(int input, int min, int max)
{
    if (input < min || input > max)
    {
        return true;
    }

    return false;
}
