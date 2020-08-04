#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include "AdjList.h"
#include "AStar.h"

using namespace std;

AStar::AStar(int verticies, vector<AdjList> graph, AdjMatrix a)
{
    totalVertices = verticies;
    adj = graph;
    matrix = a.matrix;
    ad = a;
}


//USES SAME ALGO AS DIJKSTRA BUT INSTEAD USES THE HUERISTIC TO HAVE SMART COMPARISON
void AStar::aSearchList(int startNode, int destinationNode)
{
    vector<int> path(totalVertices);
    currentPath.push_back(startNode);
    path[startNode] = -1;
    vector<int> f (totalVertices, 0);
    vector<int> cost(totalVertices, INT_MAX);
    vector<int> distance(totalVertices, 0);
    cost[startNode] = 0;
    distance[startNode] = 0;
    vector<bool> explored(totalVertices, false);
    
    for (int count = 0; count < totalVertices-1; count++)
    {
        int min = INT_MAX;
        int min_index;
        
        for (int v = 0; v < totalVertices; v++)
        {
            if (explored[v] == false && cost[v] <= min)
            {
                min = cost[v];
                min_index = v;
            }
        }
            
        
        int newNode = min_index;
        explored[newNode] = true;
    
        for (int i = 0; i < totalVertices; i++)
        {
            
            if (!explored[i] && adj[newNode - 1].connectionWeight[i] && cost[newNode] + adj[newNode - 1].connectionWeight[i] < cost[i])
            {
                f[i] = distance[newNode] * (1 + cost[i]); // HUERISTIC F(N)
                if(f[newNode] > f[i])
                {
                    exploredNodes++;
                    path[i]  = newNode;
                    distance[i] = distance[newNode] + sqrt((adj[newNode - 1].position1 * adj[newNode - 1].position1) + (adj[newNode-1].position2 * adj[newNode-1].position2) + (adj[newNode-1].position3 * adj[newNode-1].position3));
                    cost[i] = cost[newNode] + adj[newNode - 1].connectionWeight[i];
                }
                
            }
        }
    }
    totalDistance = distance[destinationNode];
    totalCost = cost[destinationNode];
    addPath(path, path[destinationNode]);
    currentPath.push_back(destinationNode);
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//USES SAME ALGO AS DIJKSTRA BUT INSTEAD USES THE HUERISTIC TO HAVE SMART COMPARISON
void AStar::aSearchMatrix(int startNode, int destinationNode)
{
    
    vector<int> path(totalVertices);
    currentPath.push_back(startNode);
    path[startNode] = -1;
    vector<int> cost(totalVertices, INT_MAX);
    vector<int> distance(totalVertices, 0);
    cost[startNode] = 0;
    distance[startNode] = 0;
    vector<bool> explored(totalVertices, false);
    
    for (int count = 0; count < totalVertices-1; count++)
    {
        int min = INT_MAX;
        int min_index;
        
        for (int v = 0; v < totalVertices; v++)
        {
            if (explored[v] == false && cost[v] <= min)
            {
                min = cost[v];
                min_index = v;
            }
        }
            
        
        int newNode = min_index;
        explored[newNode] = true;
    
        for (int i = 0; i < totalVertices; i++)
        {
            if (!explored[i] && matrix[newNode][i] && cost[newNode] + matrix[newNode][i] < cost[i])
            {
                distance[i] = distance[newNode] + sqrt((ad.p1[i]*ad.p1[i]) + (ad.p2[i]*ad.p2[i]) + (ad.p3[i]*ad.p3[i]));
                exploredNodes++;
                path[i]  = newNode;
                cost[i] = cost[newNode] + matrix[newNode][i];
            }
        }
    }
    totalDistance = distance[destinationNode];
    totalCost = cost[destinationNode];
    addPath(path, path[destinationNode]);
    currentPath.push_back(destinationNode);
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AStar::addPath(vector<int> path, int node)
{
    if(path[node]==-1)
    {
        return;
    }
    addPath(path, path[node]);
    currentPath.push_back(node);
}

vector<int> AStar::returnPath()
{
    return currentPath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int AStar::returnCost()
{
    return totalCost;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int AStar::returnExploredNodes()
{
    return exploredNodes;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double AStar::returnDistance()
{
    return totalDistance;
}
