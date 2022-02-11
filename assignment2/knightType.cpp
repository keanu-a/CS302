// knightType source file

#include "knightType.h"

#include <iostream>
#include <vector>
#include <iomanip>

// ----------------------------------------------------
// ----------------- PUBLIC FUNCTIONS -----------------
// ----------------------------------------------------

// Function that initializes the board and sets all elements to 0
knightType::knightType(int dim)
{
    // Pushing back to outer vector
    for (int i = 0; i < dim; i++)
    {
        std::vector<int> temp;

        // Pushing back to inner vector<int>
        for (int j = 0; j < dim; j++)
        {
            temp.push_back(0);   
        }

        // Pushes the inner vector into outer vector
        board.push_back(temp);
        
        std::vector<int>().swap(temp); // To de-allocate the temp vector
    }

    // Setting function counter to 0
    functionsCalled = 0;
}

// Wrapper function that makes first initial call to recursive function
// bool knightType::knightTour(int r, int c) { return knightTour(r, c, 1); }

// Function outputs the boards values
void knightType::outputTour() const
{
    char letter = 'A';

    for (int i = 0; i < board.size(); i++)
    {
        // Outputting the x-axis titles
        if (i == 0) 
        {
            char tempLet = letter;

            std::cout << "   ";

            for (int markers = 0; markers < board.size(); markers++)
            {
                // Each element has room for three digits and aligned left
                std::cout << std::setw(3) << std::left << tempLet;
                tempLet++;
            }

            std::cout << std::endl;
        }

        // Outputs vector<int> inside vector
        for (int j = 0; j < board[i].size(); j++)
        {
            // Outputs the y-axis titles
            if (j == 0)
            {
                std::cout << std::setw(3) << std::left << letter;
                letter++;
            }

            // Again, each element has room for three digits and aligned left
            std::cout << std::setw(3) << std::left << board[i][j];
        }

        std::cout << std::endl;
    }
}

// ---------------------------------------------------
// ---------------- PRIVATE FUNCTIONS ----------------
// ---------------------------------------------------

bool knightType::fullBoard()
{
    for (int i = 0; i < board.size(); i++)
    {
        std::vector<int> temp = board[i];

        // Goes through each vector to see if an element == 0
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] == 0)
            {
                return false;
            }
        }
    }

    // Returns true since went through the 2D vector
    return true;
}

// std::vector<knightType::position> knightType::getAvailableMoves(int r, int c)
// {
//     std::vector<position> knightMoves;

//     if (r == 1 && c == 1)
//     {
//         knightMoves.push_back( position)
//     }
// }

// bool knightType::knightTour(int r, int c, int tourIndex)
// {
//     if (fullBoard() == true) { return true; }

//     getAvailableMoves(r, c);
// }