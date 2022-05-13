// Keanu Aloua
// May 5, 2022

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

bool dfs(
    std::string current, 
    std::string searchName, 
    std::unordered_map<std::string, std::list<std::string>> famTree, 
    std::unordered_map<std::string, bool> &visited,
    std::unordered_map<std::string, bool> &ancestors);

int main() {

    std::unordered_map< std::string, std::list<std::string> > famTree;
    std::unordered_map<std::string, bool> hasAncestor;
    std::vector<std::string> names;
    std::vector<std::string> noAncestors;

    std::string filename, line, parse;
    std::string from, to;
    std::string arrow = "->";

    // Asking for input file
    std::cout << "Enter file: ";
    std::cin >> filename;
    std::cout << std::endl;

    std::ifstream infile(filename);

    // Begin parsing file
    while (std::getline(infile, line)) {

        // Grabs string from left of ->
        from = line.substr(0, line.find(arrow) - 1);

        // Grabs string right of ->
        to = line.erase(0, line.find(arrow) + arrow.length() + 1);

        famTree[from].push_back(to);

        names.push_back(from);
        names.push_back(to);
    }

    // Sorts vector
    std::sort(names.begin(), names.end());

    // Removes duplicates
    names.erase(std::unique(names.begin(), names.end()), names.end());

    // Checks which nodes have ancestors
    for (int i = 0; i < names.size(); i++) {

        // Goes through each linked list
        for (auto desc = famTree[names[i]].begin(); desc != famTree[names[i]].end(); desc++) {

            // If list is not empty, all nodes in the list have ancestors
            if (!famTree[names[i]].empty()) {
                hasAncestor[*desc] = true;
            }
        }
    }

    // Creates vector of names that have no ancestors
    for (int i = 0; i < names.size(); i++) {
        if (!hasAncestor[names[i]]) {
            noAncestors.push_back(names[i]);
        }
    }

    // ------------------------ //
    // Start Depth First Search //
    // ------------------------ //

    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, bool> ancestors;

    // Going through all nodes
    for (int i = 0; i < names.size(); i++) {

        std::cout << "Relative Name: " << names[i] << std::endl;

        // Setting both maps keys to false
        for (int i = 0; i < names.size(); i++) {
            visited[names[i]] = false;
            ancestors[names[i]] = false;
        }

        // Nodes with no ancestors
        for (int j = 0; j < noAncestors.size(); j++) {
            ancestors[noAncestors[j]] = dfs(noAncestors[j], names[i], famTree, visited, ancestors);
        }

        // Printing out ancestors
        bool hasNone = false;
        std::cout << "List of ancestors" << std::endl;

        for (int i = 0; i < names.size(); i++) {
            if (ancestors[names[i]]) {
                std::cout << names[i] << std::endl;
                hasNone = true;
            }
        }

        // Checks bool to see if there are no ancestors
        if (!hasNone) { std::cout << "None" << std::endl; }

        std::cout << std::endl;
    }

    return 0;
}

bool dfs(
    std::string current, 
    std::string searchName, 
    std::unordered_map<std::string, std::list<std::string>> famTree, 
    std::unordered_map<std::string, bool> &visited,
    std::unordered_map<std::string, bool> &ancestors) {

    // Mark current node as visited
    visited[current] = true;

    // If current == searchName, then nothing to search
    if (current == searchName) { return false; }

    // Not found, so checks if the list is empty
    if (famTree[current].empty()) { return false; }

    // Not found, then traverse through the linked list
    for (auto desc = famTree[current].begin(); desc != famTree[current].end(); desc++) {

        if (*desc == searchName) {
            ancestors[current] = true;
        }

        if (dfs(*desc, searchName, famTree, visited, ancestors)) {
            ancestors[current] = true;
        }
    }

    // If current is an ancestor, return true
    if (ancestors[current]) { return true; }

    return false;
}