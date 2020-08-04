#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <list>
#include <cmath>
#include "Dijkstra.h"
#include "AdjList.h"

using namespace std;

Dijkstra::Dijkstra(int verticies, vector<AdjList> graph, AdjMatrix a)
{
    totalVertices = verticies;
    adj = graph;
    matrix = a.matrix;
    ad = a;
}

void Dijkstra::dijkstraSearchList(int startNode, int destinationNode)
{
    int path [totalVertices];
    currentPath.push_back(startNode);
    path[startNode] = -1;
    vector<int> cost(totalVertices, INT_MAX);
    vector<int> distance(totalVertices, 0);
    cost[startNode] = 0;
    vector<bool> explored(totalVertices, false);
    //CREATES VARIBLES
    
    for (int x = 0; x < totalVertices-1; x++)
    {
        int min = INT_MAX;
        int currMin;
        //SETS MINIMUM AMOUNT
        
        for (int j = 0; j < totalVertices; j++)
        {
            if (explored[j] == false && cost[j] <= min)
            {
                min = cost[j];
                currMin = j;
            }
        }
            
        
        int newNode = currMin;
        explored[newNode] = true;
        //MARKED AS TRUE TO SHOW EXPLORATION
    
        for (int i = 0; i < totalVertices; i++)
        {
            
            if (!explored[i] && adj[newNode - 1].connectionWeight[i] && cost[newNode] + adj[newNode - 1].connectionWeight[i] < cost[i])//UPDATE ONLY IF THE TOTAL WEIGHT IS SMALLER THAT CURRENT WEIGHT
            {
                exploredNodes++;
                path[i]  = newNode;
                distance[i] = distance[newNode] + sqrt((adj[newNode - 1].position1 * adj[newNode - 1].position1) + (adj[newNode-1].position2 * adj[newNode-1].position2) + (adj[newNode-1].position3 * adj[newNode-1].position3));
                cost[i] = cost[newNode] + adj[newNode - 1].connectionWeight[i];
                //UPDATE ALL VARIBLES
            }
        }
    }
    totalDistance = distance[destinationNode];
    totalCost = cost[destinationNode];
    addPath(path, destinationNode);
    currentPath.push_back(destinationNode);
    //SETS VALUES
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dijkstra::dijkstraSearchMatrix(int startNode, int destinationNode)
{
    
    int path[totalVertices];
    currentPath.push_back(startNode);
    path[startNode] = -1;
    vector<int> cost(totalVertices, INT_MAX);
    vector<int> distance(totalVertices, 0);
    cost[startNode] = 0;
    vector<bool> explored(totalVertices, false);
    
    for (int x = 0; x < totalVertices-1; x++)
    {
        int min = INT_MAX;
        int currMin;
        
        for (int j = 0; j < totalVertices; j++)
        {
            if (explored[j] == false && cost[j] <= min)
            {
                min = cost[j];
                currMin = j;
            }
        }
            
        
        int newNode = currMin;
        explored[newNode] = true;
        //MARKED AS TRUE TO SHOW EXPLORATION
        
        for (int i = 0; i < totalVertices; i++)
        {
            if (!explored[i] && matrix[newNode][i] && cost[newNode] + matrix[newNode][i] < cost[i])//UPDATE ONLY IF THE TOTAL WEIGHT IS SMALLER THAT CURRENT WEIGHT
            {
                distance[i] = distance[newNode] + sqrt((ad.p1[newNode]*ad.p1[newNode]) + (ad.p2[newNode]*ad.p2[newNode]) + (ad.p3[newNode]*ad.p3[newNode]));
                exploredNodes++;
                path[i]  = newNode;
                cost[i] = cost[newNode] + matrix[newNode][i];
                //UPDATE ALL VARIBLES
            }
        }
    }
    
    totalDistance = distance[destinationNode];
    totalCost = cost[destinationNode];
    addPath(path, destinationNode);
    currentPath.push_back(destinationNode);
    //SETS VALUES
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dijkstra::addPath(int path [], int node)
{
    if(path[node]==-1)
    {
        return;
    }
    addPath(path, path[node]);
    currentPath.push_back(node);
    //DISPLAYS ALL IN PATH
}

vector<int> Dijkstra::returnPath()
{
    return currentPath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Dijkstra::returnCost()
{
    return totalCost;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Dijkstra::returnExploredNodes()
{
    return exploredNodes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Dijkstra::returnDistance()
{
    return totalDistance;
}
