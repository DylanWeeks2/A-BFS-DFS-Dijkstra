#ifndef DFS_h
#define DFS_h
#include "AdjList.h"
#include "AdjMatrix.h"

class DFS
{
public:
    DFS(int vertices, vector<AdjList> graph, AdjMatrix a);
    void depthFirstSearchIterativeList(int startNode, int destinationNode);
    void depthFirstSearchRecursiveList(int startNode, int destinationNode);
    void depthFirstSearchRecursiveCallList(int startNode, vector<int> finalPath, vector<bool> explored, stack<vector<int>> stack);
    void depthFirstSearchIterativeMatrix(int startNode, int destinationNode);
    void depthFirstSearchRecursiveMatrix(int startNode, int destinationNode);
    void depthFirstSearchRecursiveCallMatrix(int startNode, vector<int> finalPath, vector<bool> explored, stack<vector<int>> stack);
    vector<int> returnPath();
    int returnCost();
    int returnExploredNodes();
    double returnDistance();
    
private:
    AdjMatrix ad;
    int totalVertices = 0;
    vector<AdjList> adj;
    int** matrix;
    vector<int> currentPath;
    int totalCost = 0;
    int exploredNodes = 0;
    int destination = 0;
    double totalDistance = 0;
};

#endif /* DFS_h */
