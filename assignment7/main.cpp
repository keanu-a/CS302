// Keanu Aloua
// April 5, 2022
// UPDATED: April 9, 2022
// CS 302 - Assignment 7
// Making a custom hashmap to count ballots and declare a party winner

#include <iostream>
#include <string>
#include <fstream>

#include "hashmap.h"

int main() {

    // Hashmap and file read variables
    hashMap<std::string, int> votes;
    hashMap<std::string, std::string> candParties;
    int cases, candidates, ballots;
    std::string name, party;

    // File I/O variables
    std::string filename;
    std::ifstream infile;

    std::cout << "Enter filename: ";
    std::cin >> filename;

    infile.open(filename);
    infile >> cases;

    // Going through each case
    for (int i = 1; i <= cases; i++) {
        infile >> candidates;
        infile.ignore();

        // Adding the name + party into a hashmap
        // Adding the name + vote count into a hashmap
        for (int j = 0; j < candidates; j++) {
            std::getline(infile, name);
            std::getline(infile, party);

            candParties[name] = party;
            votes[name] = 0;
        }

        infile >> ballots;
        infile.ignore();

        // Going through each vote and keeping count
        for (int i = 0; i < ballots; i++) {
            std::getline(infile, name);
            votes[name]++;
        }

        // Going through linked list to see number of votes
        hashMap<std::string, int>::iterator max, start, end = votes.end();
        bool tie = false;
        max = votes.begin(); // Gets first node in linked list
        start = votes.begin()++; // Gets second node in linked list

        // Start traversing through linked list
        while (start != end) {
            if (start.second() > max.second()) { 
                // If node is bigger than max, set max to be node
                max = start; 
            } 
            else if (start.second() == max.second()) { 
                // If two candidates are equal, then there was a tie
                tie = true;
                break;
            }

            start++;
        }

        if (tie) { 
            std::cout << "Case " << i << " results: Tie" << std::endl; 
        }
        else { 
            std::cout << "Case " << i << " results: " << candParties[max.first()] << std::endl; 
        }

        // End of Case
    }

    infile.close();

    return 0;
}