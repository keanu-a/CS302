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

struct linkNode {
    std::string indicator;
    int pathWeight;
};

void findCheapPath(
    std::string startNode,
    std::string endNode,
    std::unordered_map< std::string, std::list<linkNode> > paths,
    std::vector<std::string> keyNames,
    std::unordered_map<std::string, std::string> &predecessor,
    std::unordered_map<std::string, int> &weights);

int main() {

    std::string filename;
    std::string startNode, endNode;
    std::string from, to;
    int weight;
    std::unordered_map< std::string, std::list<linkNode> > paths;
    std::unordered_map<std::string, bool> inVector;
    std::vector<std::string> keyNames;


    std::cout << "Enter file: ";
    std::cin >> filename;

    std::fstream infile(filename);

    infile >> startNode >> endNode;

    std::cout << "Start Nodes" << std::endl;
    std::cout << startNode << " to " << endNode << std::endl << std::endl;

    infile.ignore();

    while(infile >> from >> to >> weight) {
        linkNode newNode;

        newNode.indicator = to;
        newNode.pathWeight = weight;

        paths[from].push_back(newNode);

        if (!inVector[from]) {
            keyNames.push_back(from);
            inVector[from] = true;
        }
    }

    keyNames.push_back(to);

    // Done setting path weights

    std::unordered_map<std::string, std::string> predecessor;
    std::unordered_map<std::string, int> weights;

    for (int i = 0; i < keyNames.size(); i++) {
        predecessor[keyNames[i]] = -1;
        weights[keyNames[i]] = 0;
    }

    findCheapPath(startNode, endNode, paths, keyNames, predecessor, weights);

    return 0;
}

void findCheapPath(
    std::string startNode,
    std::string endNode,
    std::unordered_map< std::string, std::list<linkNode> > paths,
    std::vector<std::string> keyNames,
    std::unordered_map<std::string, std::string> &predecessor,
    std::unordered_map<std::string, int> &weights) {

    std::unordered_map<std::string, int> endPathWeights;

    for (auto desc = paths[startNode].begin(); desc != paths[startNode].end(); desc++) {

        std::string newStart = desc->indicator;
        int weightDifference = 0;

        // Setting predecessor and weights arrays
        predecessor[newStart] = startNode;

        if (weights[startNode] != 0) {
            weightDifference = weights[newStart] - weights[startNode];
            weights[newStart] = weightDifference;
        } else {
            weights[newStart] = desc->pathWeight;
        }

        std::cout << startNode << " has a path weight of " << weights[newStart] << " to " << newStart << std::endl;

        findCheapPath(newStart, endNode, paths, keyNames, predecessor, weights);
    }

    return;
}