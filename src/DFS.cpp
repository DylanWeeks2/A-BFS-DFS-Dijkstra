#include <stdio.h>
#include <stack>
#include <iostream>
#include <vector>
#include <cmath>
#include "DFS.h"
#include "AdjList.h"
#include "AdjMatrix.h"

using namespace std;

DFS::DFS(int vertices, vector<AdjList> graph, AdjMatrix a)
{
    adj = graph;
    totalVertices = vertices;
    matrix = a.matrix;
    ad = a;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS::depthFirstSearchIterativeList(int startNode, int destinationNode)
{
    stack<vector<int>> stack;
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    stack.push(finalPath);
    
    while (!stack.empty())
    {
        finalPath = stack.top();
        stack.pop();
        int finalNode =finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
        
        if (finalNode == destinationNode) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE (FIRST OCCURENCE)
        {
            
            currentPath = finalPath;
            
            for (int i = 0; i < finalPath.size(); i++)
            {
                totalDistance = totalDistance + sqrt((adj[finalPath[i]-1].position1 * adj[finalPath[i]-1].position1) + (adj[finalPath[i]-1].position2 * adj[finalPath[i]-1].position2) + (adj[finalPath[i]-1].position3 * adj[finalPath[i]-1].position3));
                
                
                totalCost = totalCost + adj[finalPath[i]-1].connectionWeight[finalPath[i+1]];
                
                //ADDS UP TOTAL COST AND DISTANCE OF EVERY NODE ON THE FINALPATH
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
                stack.push(tempPath);
                //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS::depthFirstSearchRecursiveList(int startNode, int destinationNode)
{
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    vector<bool> explored(totalVertices, false);
    stack<vector<int>> stack;
    stack.push(finalPath);
    destination = destinationNode;
    depthFirstSearchRecursiveCallList(startNode, finalPath, explored, stack);
}

void DFS::depthFirstSearchRecursiveCallList(int startNode, vector<int> finalPath, vector<bool> explored, stack<vector<int>> stack)
{
    finalPath = stack.top();
    stack.pop();
    int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
           
    if (finalNode == destination) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
    {
        currentPath = finalPath;
        for (int i = 1; i < finalPath.size(); i++)
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
            stack.push(tempPath);
            //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
        }
    }
    depthFirstSearchRecursiveCallList(startNode, finalPath, explored, stack);
    //RECURSIVLEY CALLS FUNCTION TO IPERATE JUST AS A LOOP
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS::depthFirstSearchIterativeMatrix(int startNode, int destinationNode)
{
    stack<vector<int>> stack;
    vector<bool> explored(totalVertices, false);
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    stack.push(finalPath);
    
    while (!stack.empty())
    {
        finalPath = stack.top();
        stack.pop();
        int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
        
        if (finalNode == destinationNode) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
        {
            currentPath = finalPath;
            for(int i = 1; i < finalPath.size(); i++)
            {
                totalDistance = totalDistance + sqrt((ad.p1[i-1]*ad.p1[i-1]) + (ad.p2[i-1]*ad.p2[i-1]) + (ad.p3[i-1]*ad.p3[i-1]));
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
                stack.push(tempPath);
                //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS::depthFirstSearchRecursiveMatrix(int startNode, int destinationNode)
{
    vector<int> finalPath;
    finalPath.push_back(startNode);
    exploredNodes++;
    vector<bool> explored(totalVertices, false);
    stack<vector<int>> stack;
    stack.push(finalPath);
    destination = destinationNode;
    depthFirstSearchRecursiveCallMatrix(startNode, finalPath, explored, stack);
}

void DFS::depthFirstSearchRecursiveCallMatrix(int startNode, vector<int> finalPath, vector<bool> explored, stack<vector<int>> stack)
{
    finalPath = stack.top();
    stack.pop();
    int finalNode = finalPath[finalPath.size() - 1]; //SETS FINAL NODE OF CURRENT VECTOR PATH
           
    if (finalNode == destination) //CHECKS TO SEE IF THE FINAL NODE EQUALS THE DESTINAITON NODE
    {
        currentPath = finalPath;
        for(int i = 1; i <= finalPath.size(); i++)
        {
            totalDistance = totalDistance + sqrt((ad.p1[i-1]*ad.p1[i-1]) + (ad.p2[i-1]*ad.p2[i-1]) + (ad.p3[i-1]*ad.p3[i-1]));
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
            stack.push(tempPath);
            //CREATES NEW VECTOR AND THE ADDS NEW UNEXPLORED NODE, THEN PUSHES ONTO STACK
        }
    }
    depthFirstSearchRecursiveCallMatrix(startNode, finalPath, explored, stack);
    //RECURSIVLEY CALLS FUNCTION TO IPERATE JUST AS A LOOP
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> DFS::returnPath()
{
    return currentPath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DFS::returnCost()
{
    return totalCost;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DFS::returnExploredNodes()
{
    return exploredNodes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double DFS::returnDistance()
{
    return totalDistance;
}
