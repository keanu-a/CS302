// Path type

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

class weightedGraph {

    struct linkNode {
        std::string name;
        int weight;
    };

    weightedGraph();
    ~weightedGraph();
    void addLink(std::string, linkNode);
    void getWeight();

    private:
        std::unordered_map<std::string, std::list<linkNode> > pathWeights;
};

void weightedGraph::addLink(std::string name, linkNode newNode) {
    pathWeights[name].push_back(newNode);

    return;
}

// Printing path weights

for (int i = 0; i < keyNames.size(); i++) {
    
    std::cout << keyNames[i] << " has paths to:" << std::endl;

    for (
        auto desc = pathWeights[keyNames[i]].begin(); 
        desc != pathWeights[keyNames[i]].end(); 
        desc++) {
        
        std::cout << desc->indicator << " with path weight of " << desc->pathWeight << std::endl;
    }

    std::cout << std::endl;
}

// Dijkstra Algo
void dijkstra(
    std::string start,
    std::string end,
    std::unordered_map< std::string, std::list<linkNode> > pathWeights,
    std::vector<std::string> keyNames) {

    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, std::string> predecessor;
    std::unordered_map<std::string, int> weights;
    std::priority_queue<int> PQ;

    for (int i = 0; i < keyNames.size(); i++) {
        visited[keyNames[i]] = false;
        predecessor[keyNames[i]] = -1;
        weights[keyNames[i]] = 9999;
    }

    return;
}

// TEMP MAIN 

//struct linkNode {
    std::string indicator;
    int pathWeight;
};

int main() {

    std::string filename;
    std::string startNode, endNode;
    std::string from, to;
    int weight;
    std::unordered_map< std::string, std::list<linkNode> > pathWeights;
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

        pathWeights[from].push_back(newNode);

        if (!inVector[from]) {
            keyNames.push_back(from);
            inVector[from] = true;
        }
    }

    // Done setting path weights

    

    return 0;
}

// MAY 12
void findCheapPath(
    std::string startNode,
    std::string endNode,
    std::unordered_map< std::string, std::list<linkNode> > paths,
    std::vector<std::string> keyNames,
    std::unordered_map<std::string, std::string> &predecessor,
    std::unordered_map<std::string, int> &weights,
    std::vector<int> &weightTracker) {

    std::unordered_map<std::string, int> endPathWeights;

    for (auto desc = paths[startNode].begin(); desc != paths[startNode].end(); desc++) {

        std::string newStart = desc->indicator; // "start: two, newStart: five"
        int weightDifference;

        // Setting predecessor and weights arrays
        predecessor[newStart] = startNode;

        // Setting weight from start to newStart
        weights[newStart] = desc->pathWeight;
        weightDifference = desc->pathWeight;

        if (weightTracker.size() > 1)
        {
            int temp = 0;

            // Calculate the new weight
            for (int i = 0; i < weightTracker.size(); i++) 
            {
                
            }
        }

        // Keep track of weights in order
        weightTracker.push_back(weightDifference); // 60

        std::cout << startNode << " has a path weight of " << weights[newStart] << " to " << newStart << std::endl;

        findCheapPath(newStart, endNode, paths, keyNames, predecessor, weights, weightTracker);
    }

    return;
}

// Another test of dijkstras
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

    auto path1 = paths[startNode].begin(); 

    priorityQueue.insert(*path1);

    while(!priorityQueue.isEmpty()) {
        trainPath min = priorityQueue.getPriority();
        priorityQueue.deletePriority();

        weights[min.indicator] = min.pathWeight;

        for (auto path = paths[min.indicator].begin(); path != paths[min.indicator].end(); path++) {
            
            int combinedWeight = weights[min.indicator] + path->pathWeight;

            if (path->pathWeight)

        }
    }


    return;
}