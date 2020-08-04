#include <stdio.h>
#include <queue>
#include <iostream>
#include <vector>
#include <cmath>
#include "BFS.h"
#include "AdjList.h"
#include "AdjMatrix.h"

using namespace std;

BFS::BFS(int vertices, vector<AdjList> graph, AdjMatrix a)
{
    adj = graph;
    totalVertices = vertices;
    matrix = a.matrix;
    ad = a;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BFS::breadthFirstSearchIterativeList(int startNode, int destinationNode)
{
    queue<vector<int>> queue;
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    queue.push(finalPath);
    
    while (!queue.empty())
    {
        finalPath= queue.front();
        queue.pop();
        int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
        
        if (finalNode == destinationNode) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
        {
            
            currentPath = finalPath;
            
            for (int i = 0; i < finalPath.size(); i++)
            {
                
                totalDistance = totalDistance + sqrt((adj[finalPath[i]-1].position1 * adj[finalPath[i]-1].position1) + (adj[finalPath[i]-1].position2 * adj[finalPath[i]-1].position2) + (adj[finalPath[i]-1].position3 * adj[finalPath[i]-1].position3));
                
                totalCost = totalCost + adj[finalPath[i]-1].connectionWeight[finalPath[i+1]];
                //ADDS UP TOTAL COST OF EVERY NODE ON THE FINALPATH
            }
            break;
            //BREAKS FROM LOOP BECAUSE IT FOUND THE FIRST AVALIBLE PATH
        }

        for (int i = 0; i < adj[finalNode-1].connectingNodes.size(); i++)
        {
            if (!explored[adj[finalNode-1].connectingNodes[i]])
            {
                explored[adj[finalNode-1].connectingNodes[i]] = true;
                exploredNodes++;
                //MARKS THE CURRENT NODE AS EXPLORED AND ADDS TO NODE EXPLORED COUNT
                
                vector<int> tempPath = finalPath;
                tempPath.push_back(adj[finalNode-1].connectingNodes[i]);
                
                
                queue.push(tempPath);
                //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BFS::breadthFirstSearchRecursiveList(int startNode, int destinationNode)
{
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    queue<vector<int>> queue;
    queue.push(finalPath);
    destination = destinationNode;
    breadthFirstSearchRecursiveCallList(startNode, finalPath, explored, queue);
}

void BFS::breadthFirstSearchRecursiveCallList(int startNode, vector<int> finalPath, vector<bool> explored, queue<vector<int>> queue)
{
    finalPath = queue.front();
    queue.pop();
    int finalNode = finalPath[finalPath.size() - 1];
    
    if (finalNode == destination) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
    {
        currentPath =finalPath;
        for (int i = 0; i < finalPath.size(); i++)
        {
            totalDistance = totalDistance + sqrt((adj[finalPath[i]-1].position1 * adj[finalPath[i]-1].position1) + (adj[finalPath[i]-1].position2 * adj[finalPath[i]-1].position2) + (adj[finalPath[i]-1].position3 * adj[finalPath[i]-1].position3));
            totalCost = totalCost + adj[finalPath[i]-1].connectionWeight[finalPath[i+1]];
            //ADDS UP TOTAL COST OF EVERY NODE ON THE FINALPATH
        }
        return;
        //BREAKS FROM LOOP BECAUSE IT FOUND THE FIRST AVALIBLE PATH
    }

    for (int i = 0; i < adj[finalNode-1].connectingNodes.size(); i++)
    {
        if (!explored[adj[finalNode-1].connectingNodes[i]])
        {
            explored[adj[finalNode-1].connectingNodes[i]] = true;
            exploredNodes++;
            //MARKS THE CURRENT NODE AS EXPLORED AND ADDS TO NODE EXPLORED COUNT
            
            vector<int> tempPath = finalPath;
            tempPath.push_back(adj[finalNode-1].connectingNodes[i]);
            queue.push(tempPath);
            //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
        }
    }
    breadthFirstSearchRecursiveCallList(startNode, finalPath, explored, queue);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BFS::breadthFirstSearchIterativeMatrix(int startNode, int destinationNode)
{

    queue<vector<int>> queue;
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    queue.push(finalPath);
    
    while (!queue.empty())
    {
        finalPath = queue.front();
        queue.pop();
        int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
        
        if (finalNode == destinationNode) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
        {
            currentPath = finalPath;
            for(int i = 1; i < finalPath.size(); i++)
            {
                totalDistance = totalDistance + sqrt((ad.p1[i]*ad.p1[i]) + (ad.p2[i]*ad.p2[i]) + (ad.p3[i]*ad.p3[i]));
                totalCost = totalCost + matrix[currentPath[i-1]][currentPath[i]];
            }
            break;
            //BREAKS FROM LOOP BECAUSE IT FOUND THE FIRST AVALIBLE PATH
        }

        for (int i = 1; i <= totalVertices; i++)
        {
            if (matrix[finalNode][i] >= 1 && (!explored[i]))
            {
                explored[i] = true;
                exploredNodes++;
                //MARKS THE CURRENT NODE AS EXPLORED AND ADDS TO NODE EXPLORED COUNT
                
                vector<int> tempPath = finalPath;
                tempPath.push_back(i);
                queue.push(tempPath);
                //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BFS::breadthFirstSearchRecursiveMatrix(int startNode, int destinationNode)
{
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    queue<vector<int>> queue;
    queue.push(finalPath);
    destination = destinationNode;
    breadthFirstSearchRecursiveCallMatrix(startNode, finalPath, explored, queue);
}

void BFS::breadthFirstSearchRecursiveCallMatrix(int startNode, vector<int> finalPath, vector<bool> explored, queue<vector<int>> queue)
{
    finalPath = queue.front();
    queue.pop();
    int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
    
    if (finalNode == destination) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
    {
        currentPath = finalPath;
        for(int i = 1; i < finalPath.size(); i++)
        {
            totalDistance = totalDistance + sqrt((ad.p1[i]*ad.p1[i]) + (ad.p2[i]*ad.p2[i]) + (ad.p3[i]*ad.p3[i]));
            totalCost = totalCost + matrix[currentPath[i-1]][currentPath[i]];
        }
        return;
        //BREAKS FROM LOOP BECAUSE IT FOUND THE FIRST AVALIBLE PATH
    }

    for (int i = 1; i <= totalVertices; i++)
    {
        if (matrix[finalNode][i] >= 1 && (!explored[i]))
        {
            explored[i] = true;
            exploredNodes++;
            //MARKS THE CURRENT NODE AS EXPLORED AND ADDS TO NODE EXPLORED COUNT
            
            vector<int> tempPath = finalPath;
            tempPath.push_back(i);
            queue.push(tempPath);
            //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
        }
    }
    breadthFirstSearchRecursiveCallMatrix(startNode, finalPath, explored, queue);
}

vector<int> BFS::returnPath()
{
    return currentPath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BFS::returnCost()
{
    return totalCost;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BFS::returnExploredNodes()
{
    return exploredNodes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double BFS::returnDistance()
{
    return totalDistance;
}
