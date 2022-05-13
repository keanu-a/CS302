// Keanu Aloua
// May 6, 2022
// Extra Credit Assignment

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <vector>

#include "priority-queue.h"

void findCheapestPath(
    std::string startNode, 
    std::string endNode, 
    std::unordered_map< std::string, std::list<trainPath> > paths, 
    std::vector<std::string> vertices);

int main() {

    std::string filename;
    std::string startNode, endNode;
    std::string from, to;
    int weight;
    std::unordered_map< std::string, std::list<trainPath> > paths;
    std::unordered_map<std::string, bool> inVector;
    std::vector<std::string> vertices;


    std::cout << "Enter file: ";
    std::cin >> filename;

    std::fstream infile(filename);

    infile >> startNode >> endNode;

    std::cout << "Start Nodes" << std::endl;
    std::cout << startNode << " to " << endNode << std::endl << std::endl;

    infile.ignore();

    while(infile >> from >> to >> weight) {
        trainPath newNode;

        newNode.indicator = to;
        newNode.pathWeight = weight;

        paths[from].push_back(newNode);

        if (!inVector[from]) {
            vertices.push_back(from);
            inVector[from] = true;
        }
    }

    vertices.push_back(to);

    priorityQ<trainPath> priorityQueue;

    // Done setting path weights

    findCheapestPath(startNode, endNode, paths, vertices);

    return 0;
}

void findCheapestPath(
    std::string startNode, 
    std::string endNode, 
    std::unordered_map< std::string, std::list<trainPath> > paths, 
    std::vector<std::string> vertices) {

    std::unordered_map<std::string, std::string> predecessor;
    std::unordered_map<std::string, int> weights;
    priorityQ<trainPath> priorityQueue;

    for (int i = 0; i < vertices.size(); i++) {
        predecessor[vertices[i]] = -1;
        weights[vertices[i]] = 0;
    }

    for (auto path = paths[startNode].begin(); path != paths[startNode].end(); path++) {
        priorityQueue.insert(*path);
    }

    return;
}