#ifndef SearchAlgorithms_h
#define SearchAlgorithms_h
#include <iostream>
#include <vector>
#include "Algortithms.h"
#include "AdjList.h"
#include "AdjMatrix.h"

using namespace std;
using namespace std::chrono;


class SearchAlgorithms : public Algorithms
{

public:
    virtual void load(char* argv[]);
    virtual void select(int algorithm, int adjType);
    virtual void execute();
    virtual void stats();
    virtual void save(int i);
    
private:
    int source = 0;
    int destination = 0;
    vector<AdjList> graph;
    AdjMatrix adjM;
    string algorithmType;
    string adj;
    vector<int> path;
    int totalCost;
    int numberOfExploredNodes;
    int totalDistance;
    double executionTime;
    int iterativeOrRecursive;
    bool alreadyLoaded = false;
    int averageDistanceList[7];
    int averageExploredList[7];
    int averageTimeList[7];
    int averageCostList[7];
    double averageNodesList[7];
    int averageDistanceMatrix[7];
    int averageExploredMatrix[7];
    int averageTimeMatrix[7];
    int averageCostMatrix[7];
    double averageNodesMatrix[7];
    
};
#endif /* SearchAlgorithms_h */
