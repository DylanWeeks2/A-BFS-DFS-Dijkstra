#ifndef AStar_h
#define AStar_h
#include <vector>
#include "AdjList.h"
#include "AdjMatrix.h"

using namespace std;

class AStar
{
public:
    AStar(int vertices, vector<AdjList> graph, AdjMatrix a);
    void aSearchList(int startNode, int destinationNode);
    void aSearchMatrix(int startNode, int destinationNode);
    void addPath(vector<int> path, int node);
    vector<int> returnPath();
    int returnCost();
    int returnExploredNodes();
    double returnDistance();
    
private:
    AdjMatrix ad;
    int totalVertices = 0;
    int ** matrix;
    vector<AdjList> adj;
    vector<int> currentPath;
    int totalCost = 0;
    int exploredNodes = 0;
    int destination = 0;
    double totalDistance = 0;
};



#endif /* AStar_h */
