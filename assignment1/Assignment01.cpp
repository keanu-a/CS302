// Keanu Aloua
// CS 302 - Review from CS 202 using Linked List
// Bubble Sort of a double linked list

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "linked_list.h"

int main()
{
    std::string file;

    // Get file name from user
    std::cout << "Enter file with list: ";
    std::cin >> file;

    std::ifstream infile;
    infile.open(file);

    int num;
    LL<int> list;

    // Reads numbers from file and puts into list
    while (infile >> num)
    {
        list.tailInsert(num);
    }

    // -------- PRINT Sorted List --------
    LL<int>::iterator it = list.begin();
    LL<int>::iterator nil(NULL);

    std::cout << "Original List" << std::endl;
    while (it != nil)
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl << std::endl;

    // -------- START BUBBLE SORT --------
    LL<int>::iterator i = NULL; // Setting i to NULL

    while (i != list.begin())
    {
        LL<int>::iterator j = list.begin(); // First iterator
        LL<int>::iterator temp = j;
        temp++; // Second iterator

        while (temp != i) // Loop stops when temp == i
        {
            if (*j > *temp)
            {
                list.swapNodes(j, temp);
            }

            // Gets next nodes
            j++; 
            temp++;
        }

        if (i == NULL) { i = list.end(); } // If first sort then i == max node
        else { i--; } // Else decrement stop
    }
    // -------- END BUBBLE SORT --------

    // -------- Print Sorted List --------
    // Same code as printing unsorted list
    it = list.begin();
    nil = NULL;

    std::cout << "Sorted List" << std::endl;
    while (it != nil)
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl << std::endl;

    list.~LL();

    return 0;
}