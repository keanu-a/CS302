// Keanu Aloua
// Assignment 2 - Recursion
// CS 302 - 1002

#ifndef KNIGHTTYPE_H
#define KNIGHTTYPE_H

#include <iostream>
#include <vector>
#include <iomanip>

class knightType
{
public:
    struct position
    {
        position(int r = 0, int c = 0, int o = 0)
        {
            row = r;
            col = c;
            onwardMoves = o;
        }

        int row;
        int col;
        int onwardMoves;
    };

    knightType(int = 8);
    bool knightTour(int , int);
    void outputTour() const;

private:
    bool knightTour(int, int, int);
    std::vector<position> getAvailableMoves(int, int);
    bool fullBoard();

    // Helper functions
    std::vector<position> sortList(std::vector<position>);
    int getOnward(int, int); 
    
    std::vector< std::vector<int> > board;
    int functionsCalled;
};

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

// Wrapper function, initial call to recurisve function
bool knightType::knightTour(int r, int c)
{
    return knightTour(r, c, 1);
}

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

    std::cout << std::endl;
    std::cout << "Functions called: " << functionsCalled << std::endl;
}

// ---------------------------------------------------
// ---------------- PRIVATE FUNCTIONS ----------------
// ---------------------------------------------------

bool knightType::knightTour(int r, int c, int tourIndex)
{
    std::vector<position> avMoves; // Initializing a vector
    int listSize; // Keeping track of list size
    
    // Incremenet functionsCalled count
    functionsCalled++;

    // 1. Setting the board space
    board[r][c] = tourIndex;

    // 2. Checking if the board is full
    if (fullBoard() == true) {
        return true;
    }

    // 3. Getting vector of available moves
    avMoves = getAvailableMoves(r, c);
    listSize = avMoves.size();

    // 4. Checks if list is empty
    if (listSize == 0) { 
        board[r][c] = 0; // Setting position back to 0

        return false; 
    }

    // 5. Incrementing tour index
    tourIndex++;

    // 6. Sorts list from least to greatest onward moves
    avMoves = sortList(avMoves);

    // 7. Checks if move with least onward moves is a valid move
    for (int i = 0; i < listSize; i++)
    {
        if (knightTour(avMoves[i].row, avMoves[i].col, tourIndex)) 
        {
            // If so then break out of the for loop
            break;
        }

        // Will loop through the list to find next move with least onward moves
    }

    // Back to calling function
    return true;
}

// Helper function to sort the list of position objects
std::vector<knightType::position> knightType::sortList(std::vector<knightType::position> list)
{
    // Sorts list by putting least in the front
    for (int i = 0; i < list.size(); i++)
    {
        position least = list[i]; // Default least element

        for (int j = i; j < list.size(); j++)
        {
            if (list[j].onwardMoves < least.onwardMoves)
            {
                // Swaps the new least index with default least
                std::swap(list[i], list[j]);

                // Least element is now the front element after OLD least element
                least = list[i];
            }
        }
    }

    return list;
}

// Helper Function to count how many onward moves an available move has
int knightType::getOnward(int r, int c)
{
    int moves = 0; // Counter for onward moves

    // ORDER DOESNT MATTER

    // Right 2, Up 1
    if ( (c + 2 < board[r].size()) && (r - 1 >= 0) && (board[r - 1][c + 2] == 0) ) { moves++; }
    
    // Right 1, Up 2
    if ( (c + 1 < board[r].size()) && (r - 2 >= 0) && (board[r - 2][c + 1] == 0) ) { moves++; }

    // Left 2, Up 1
    if ( (c - 2 >= 0) && (r - 1 >= 0) && (board[r - 1][c - 2] == 0) ) { moves++; }

    // Left 1, Up 2
    if ( (c - 1 >= 0) && (r - 2 >= 0) && (board[r - 2][c - 1] == 0) ) { moves++; }

    // Right 2, Down 1
    if ( (c + 2 < board[r].size()) && (r + 1 < board.size()) && (board[r + 1][c + 2] == 0) ) { moves++; }

    //Left 2, Down 1
    if ( (c - 2 >= 0) && (r + 1 < board.size()) && (board[r + 1][c - 2] == 0) ) { moves++; }

    // Right 1, Down 2
    if ( (c + 1 < board[r].size()) && (r + 2 < board.size()) && (board[r + 2][c + 1] == 0) ) { moves++; }

    // Left 1, Down 2
    if ( (c - 1 >= 0) && (r + 2 < board.size()) && (board[r + 2][c - 1] == 0) ) { moves++; }

    return moves;
}

std::vector<knightType::position> knightType::getAvailableMoves(int r, int c)
{
    std::vector<position> knightMoves;
    int count = 0;  // To keep track of vector index

    // ORDER MATTERS

    // Left 2, Up 1
    if ( (c - 2 >= 0) && (r - 1 >= 0) && (board[r - 1][c - 2] == 0) ) {
        knightMoves.push_back( position(r-1, c-2) );
        knightMoves[count].onwardMoves = getOnward(r-1, c-2); 
        count++;
    }

    // Right 2, Up 1
    if ( (c + 2 < board[r].size()) && (r - 1 >= 0) && (board[r - 1][c + 2] == 0) ) {
        knightMoves.push_back( position(r-1, c+2) );
        knightMoves[count].onwardMoves = getOnward(r-1, c+2); 
        count++;
    }
    
    // Left 1, Up 2
    if ( (c - 1 >= 0) && (r - 2 >= 0) && (board[r - 2][c - 1] == 0) ) {
        knightMoves.push_back( position(r-2, c-1) );
        knightMoves[count].onwardMoves = getOnward(r-2, c-1); 
        count++;
    }

    // Right 1, Up 2
    if ( (c + 1 < board[r].size()) && (r - 2 >= 0) && (board[r - 2][c + 1] == 0) ) {
        knightMoves.push_back( position(r-2, c+1) );
        knightMoves[count].onwardMoves = getOnward(r-2, c+1); 
        count++;
    }

    //Left 2, Down 1
    if ( (c - 2 >= 0) && (r + 1 < board.size()) && (board[r + 1][c - 2] == 0) ) {
        knightMoves.push_back( position(r+1, c-2) );
        knightMoves[count].onwardMoves = getOnward(r+1, c-2); 
        count++;   
    }

    // Right 2, Down 1
    if ( (c + 2 < board[r].size()) && (r + 1 < board.size()) && (board[r + 1][c + 2] == 0) ) {
        knightMoves.push_back( position(r+1, c+2) );
        knightMoves[count].onwardMoves = getOnward(r+1, c+2); 
        count++;
    }

    // Left 1, Down 2
    if ( (c - 1 >= 0) && (r + 2 < board.size()) && (board[r + 2][c - 1] == 0) ) {
        knightMoves.push_back( position(r+2, c-1) );
        knightMoves[count].onwardMoves = getOnward(r+2, c-1); 
        count++;
    }

    // Right 1, Down 2
    if ( (c + 1 < board[r].size()) && (r + 2 < board.size()) && (board[r + 2][c + 1] == 0) ) {
        knightMoves.push_back( position(r+2, c+1) );
        knightMoves[count].onwardMoves = getOnward(r+2, c+1); 
    }

    return knightMoves; // List of moves
}

bool knightType::fullBoard()
{
    // Loops through each position vector in the vector to see if there are still zeros
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // Returns true since there were no zeros
    return true;
}

#endif