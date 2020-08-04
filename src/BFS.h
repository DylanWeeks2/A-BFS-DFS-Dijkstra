#ifndef BFS_h
#define BFS_h
#include <queue>
#include "AdjList.h"
#include "AdjMatrix.h"

class BFS
{
public:
    BFS(int vertices, vector<AdjList> graph, AdjMatrix a);
    void breadthFirstSearchIterativeList(int startNode, int destinationNode);
    void breadthFirstSearchRecursiveList(int startNode, int destinationNode);
    void breadthFirstSearchRecursiveCallList(int startNode, vector<int> finalPath, vector<bool> explored, queue<vector<int>>);
    void breadthFirstSearchIterativeMatrix(int startNode, int destinationNode);
    void breadthFirstSearchRecursiveMatrix(int startNode, int destinationNode);
    void breadthFirstSearchRecursiveCallMatrix(int startNode, vector<int> finalPath, vector<bool> explored, queue<vector<int>>);
    vector<int> returnPath();
    int returnCost();
    int returnExploredNodes();
    double returnDistance();
    
private:
    AdjMatrix ad;
    int totalVertices;
    vector<AdjList> adj;
    int** matrix;
    vector<int> currentPath;
    int totalCost = 0;
    int exploredNodes = 0;
    double totalDistance = 0;
    int destination = 0;
};

#endif /* BFS_h */
