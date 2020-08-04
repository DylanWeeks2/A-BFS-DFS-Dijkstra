//DYLAN WEEKS, 47343235, 10/17/19
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include "SearchAlgorithms.h"
#include "DFS.h"
#include "BFS.h"
#include "AdjList.h"
#include "Dijkstra.h"
#include "AdjMatrix.h"
#include "AStar.h"

using namespace std;
using namespace std::chrono;

void SearchAlgorithms::load(char * argv[])
{
    if(alreadyLoaded == false)
    {
        //CREATES VARIBLES
        ifstream graphFile;
        ifstream weightFile;
        ifstream positionFile;
        
        graphFile.open("/Users/dylanweeks/Downloads/graph.txt");
        string line;
        string stringVertex;
        string stringNode;
        string stringWeight;
        int vertex;
        int node;
        stringstream commandLine1(argv[2]);
        commandLine1 >> source;
        stringstream commandLine2(argv[3]);
        commandLine2 >> destination;
        
        //LOADING GRAPH
        
        while(graphFile.good())
        {
            graphFile >> line;
            stringstream graphLine(line);
            getline(graphLine, stringVertex, ',');
            stringstream graphVertex(stringVertex);
            graphVertex >> vertex;
            vertex = vertex -1;
            graph.push_back(AdjList());
            //WORKS AS A ADJLIST, EVERY NEW VERTEX CREATES NEW OBJECT
            while(getline(graphLine, stringNode, ','))
            {
                stringstream graphNode(stringNode);
                graphNode >> node;
                graph[vertex].connectingNodes.push_back(node);
                //PUSHES BACK NODE ONTO CURRENT VERTEX OBJECT
            }
        }
        graphFile.close();
        
        adjM.setValues(graph.size(), graph.size());
        
        
        //LOADING POSITION
        
        positionFile.open("/Users/dylanweeks/Downloads/positions.txt");
        string p1, p2, p3;
        int position1, position2, position3;
        
        while(positionFile.good())
        {
            positionFile >> line;
            stringstream positionLine(line);
            getline(positionLine, stringVertex, ',');
            stringstream positionVertex(stringVertex);
            positionVertex >> vertex;
            vertex = vertex - 1;
            getline(positionLine, p1, ',');
            stringstream positionP1(p1);
            positionP1 >> position1;
            getline(positionLine, p2, ',');
            stringstream positionP2(p2);
            positionP2 >> position2;
            getline(positionLine, p3, '\n');
            stringstream positionP3(p3);
            positionP3 >> position3;
            graph[vertex].position1 = position1;
            graph[vertex].position2 = position2;
            graph[vertex].position3 = position3;
            adjM.p1.push_back(position1);
            adjM.p2.push_back(position2);
            adjM.p3.push_back(position3);
        }
        positionFile.close();
        
        //LOADING WEIGHTS
        
        weightFile.open("/Users/dylanweeks/Downloads/weights.txt");
        int weight;
        while (weightFile.good())
        {
            weightFile >> line;
            stringstream weightLine(line);
            getline(weightLine, stringVertex, ',');
            stringstream weightVertex(stringVertex);
            weightVertex >> vertex;
            vertex = vertex - 1;
            getline(weightLine, stringNode, ',');
            stringstream weightNode(stringNode);
            weightNode >> node;
            getline(weightLine, stringWeight, '\n');
            stringstream weightWeight(stringWeight);
            weightWeight >> weight;
            graph[vertex].connectionWeight.insert(pair<int, int>(node, weight));
            adjM.insert(vertex+1, node, weight);
            //USES MAP TO LOAD BOTH THE CONNECTING NODE AND THE WEIGHT AND LOADS TO VERTEX
        }
        weightFile.close();
    }
    else
    {
        int one = rand() % graph.size() + 1;
        int two = rand() % graph.size() + 1;
        if(one<=two)
        {
            source = one;
            destination=two;
        }
        else
        {
            source = two;
            destination = one;
        }
    }
    alreadyLoaded = true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SearchAlgorithms::select(int algorithm, int adjType)
{
    if(adjType == 0)
    {
        adj = "Adjacency List";
    }
    else
    {
        adj = "Adjacency Matrix";
    }
    
    
    if(algorithm == 0)
    {
        algorithmType = "DFS";
    }
    else if(algorithm == 1)
    {
        algorithmType = "BFS";
    }
    else if(algorithm == 2)
    {
        algorithmType = "DIJKSTRA";
    }
    else
    {
        algorithmType = "A*";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SearchAlgorithms::execute()
{
    if(adj == "List")
    {
           if(algorithmType == "DFS")
           {
               //STARTS WITH ITERATIVE SEARCH
               //CREATES DFS OBJECT AND LOADS IN TOTAL VERTECIES AND THE ADJ OBJECT
               DFS dfsIterative(graph.size(), graph, adjM);
               
               //CLOCKS THE SEARCH ALGORITHM
               high_resolution_clock::time_point start = high_resolution_clock::now();
               dfsIterative.depthFirstSearchIterativeList(source, destination);
               high_resolution_clock::time_point finish = high_resolution_clock::now();
               duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
               
               //GETS ALL THE STATS FROM THE DFS ALGORITHM
               path = dfsIterative.returnPath();
               totalCost = dfsIterative.returnCost();
               averageCostList[1] = averageCostList[1] + totalCost;
               totalDistance = dfsIterative.returnDistance();
               averageDistanceList[1] = averageDistanceList[1] + totalDistance;
               numberOfExploredNodes = dfsIterative.returnExploredNodes();
               averageNodesList[1] = averageNodesList[1] + numberOfExploredNodes;
               executionTime = timeSpan.count();
               averageTimeList[1] = averageTimeList[1] + executionTime;
               iterativeOrRecursive = 0;
               stats();
               
               //THEN DOES RECURSIVE SEARCH
               DFS dfsRecursive(graph.size(), graph, adjM);
               
               high_resolution_clock::time_point start2 = high_resolution_clock::now();
               dfsRecursive.depthFirstSearchRecursiveList(source, destination);
               high_resolution_clock::time_point finish2 = high_resolution_clock::now();
               duration<double> timeSpan2 = duration_cast<duration<double>>(finish2 - start2);
               
               //GETS ALL THE STATS FROM THE DFS ALGORITHM
               path = dfsRecursive.returnPath();
               totalCost = dfsRecursive.returnCost();
               averageCostList[2] = averageCostList[2] + totalCost;
               totalDistance = dfsRecursive.returnDistance();
               averageDistanceList[2] = averageDistanceList[2] + totalDistance;
               numberOfExploredNodes = dfsRecursive.returnExploredNodes();
               averageNodesList[2] = averageNodesList[2] + numberOfExploredNodes;
               executionTime = timeSpan2.count();
               averageTimeList[2] = averageTimeList[2] + executionTime;
               iterativeOrRecursive = 1;
               
           }
           else if(algorithmType == "BFS")
           {
               BFS bfsIterative(graph.size(), graph, adjM);
               
               //CLOCKS THE SEARCH ALGORITHM
               high_resolution_clock::time_point start = high_resolution_clock::now();
               bfsIterative.breadthFirstSearchIterativeList(source, destination);
               high_resolution_clock::time_point finish = high_resolution_clock::now();
               duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
               
               //GETS ALL THE STATS FROM THE DFS ALGORITHM
               path = bfsIterative.returnPath();
               totalCost = bfsIterative.returnCost();
               averageCostList[3] = averageCostList[3] + totalCost;
               totalDistance = bfsIterative.returnDistance();
               averageDistanceList[3] = averageDistanceList[3] + totalDistance;
               numberOfExploredNodes = bfsIterative.returnExploredNodes();
               averageNodesList[3] = averageNodesList[3] + numberOfExploredNodes;
               executionTime = timeSpan.count();
               averageTimeList[3] = averageTimeList[3] + executionTime;
               iterativeOrRecursive = 0;
               stats();
               
               BFS bfsRecursive(graph.size(), graph, adjM);
               
               //CLOCKS THE SEARCH ALGORITHM
               high_resolution_clock::time_point start2 = high_resolution_clock::now();
               bfsRecursive.breadthFirstSearchRecursiveList(source, destination);
               high_resolution_clock::time_point finish2 = high_resolution_clock::now();
               duration<double> timeSpan2 = duration_cast<duration<double>>(finish2 - start2);
               
               //GETS ALL THE STATS FROM THE DFS ALGORITHM
               path = bfsRecursive.returnPath();
               totalCost = bfsRecursive.returnCost();
               averageCostList[4] = averageCostList[4] + totalCost;
               totalDistance = bfsRecursive.returnDistance();
               averageDistanceList[4] = averageDistanceList[4] + totalDistance;
               numberOfExploredNodes = bfsRecursive.returnExploredNodes();
               averageNodesList[4] = averageNodesList[4] + numberOfExploredNodes;
               executionTime = timeSpan2.count();
               averageTimeList[4] = averageTimeList[4] + executionTime;
               iterativeOrRecursive = 1;
           }
           else if(algorithmType == "DIJKSTRA")
           {
               Dijkstra dij(graph.size(), graph, adjM);
               //CLOCKS THE SEARCH ALGORITHM
               high_resolution_clock::time_point start = high_resolution_clock::now();
               dij.dijkstraSearchList(source, destination);
               high_resolution_clock::time_point finish = high_resolution_clock::now();
               duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
               
               
               path = dij.returnPath();
               totalCost = dij.returnCost();
               averageCostList[5] = averageCostList[5] + totalCost;
               totalDistance = dij.returnDistance();
               averageDistanceList[5] = averageDistanceList[5] + totalDistance;
               numberOfExploredNodes = dij.returnExploredNodes();
               averageNodesList[5] = averageNodesList[5] + numberOfExploredNodes;
               executionTime = timeSpan.count();
               averageTimeList[5] = averageTimeList[5] + executionTime;
           }
           else
           {
               AStar a(graph.size(), graph, adjM);
               //CLOCKS THE SEARCH ALGORITHM
               high_resolution_clock::time_point start = high_resolution_clock::now();
               a.aSearchMatrix(source, destination);
               high_resolution_clock::time_point finish = high_resolution_clock::now();
               duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
               
               
               path = a.returnPath();
               totalCost = a.returnCost();
               averageCostList[6] = averageCostList[6] + totalCost;
               totalDistance = a.returnDistance();
               averageDistanceList[6] = averageDistanceList[6] + totalDistance;
               numberOfExploredNodes = a.returnExploredNodes();
               averageNodesList[6] = averageNodesList[6] + numberOfExploredNodes;
               executionTime = timeSpan.count();
               averageTimeList[6] = averageTimeList[6] + executionTime;
           }
    }
    else
    {
        if(algorithmType == "DFS")
        {
            //STARTS WITH ITERATIVE SEARCH
            //CREATES DFS OBJECT AND LOADS IN TOTAL VERTECIES AND THE ADJ OBJECT
            DFS dfsIterative(graph.size(), graph, adjM);
            
            //CLOCKS THE SEARCH ALGORITHM
            high_resolution_clock::time_point start = high_resolution_clock::now();
            dfsIterative.depthFirstSearchIterativeList(source, destination);
            high_resolution_clock::time_point finish = high_resolution_clock::now();
            duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
            
            //GETS ALL THE STATS FROM THE DFS ALGORITHM
            path = dfsIterative.returnPath();
            totalCost = dfsIterative.returnCost();
            averageCostMatrix[1] = averageCostMatrix[1] + totalCost;
            totalDistance = dfsIterative.returnDistance();
            averageDistanceMatrix[1] = averageDistanceMatrix[1] + totalDistance;
            numberOfExploredNodes = dfsIterative.returnExploredNodes();
            averageNodesMatrix[1] = averageNodesMatrix[1] + numberOfExploredNodes;
            executionTime = timeSpan.count();
            averageTimeMatrix[1] = averageTimeMatrix[1] + executionTime;
            iterativeOrRecursive = 0;
            stats();
            
            //THEN DOES RECURSIVE SEARCH
            DFS dfsRecursive(graph.size(), graph, adjM);
            
            high_resolution_clock::time_point start2 = high_resolution_clock::now();
            dfsRecursive.depthFirstSearchRecursiveList(source, destination);
            high_resolution_clock::time_point finish2 = high_resolution_clock::now();
            duration<double> timeSpan2 = duration_cast<duration<double>>(finish2 - start2);
            
            //GETS ALL THE STATS FROM THE DFS ALGORITHM
            path = dfsRecursive.returnPath();
            totalCost = dfsRecursive.returnCost();
            averageCostMatrix[2] = averageCostMatrix[2] + totalCost;
            totalDistance = dfsRecursive.returnDistance();
            averageDistanceMatrix[2] = averageDistanceMatrix[2] + totalDistance;
            numberOfExploredNodes = dfsRecursive.returnExploredNodes();
            averageNodesMatrix[2] = averageNodesMatrix[2] + numberOfExploredNodes;
            executionTime = timeSpan2.count();
            averageTimeMatrix[2] = averageTimeMatrix[2] + executionTime;
            iterativeOrRecursive = 1;
            
        }
        else if(algorithmType == "BFS")
        {
            BFS bfsIterative(graph.size(), graph, adjM);
            
            //CLOCKS THE SEARCH ALGORITHM
            high_resolution_clock::time_point start = high_resolution_clock::now();
            bfsIterative.breadthFirstSearchIterativeList(source, destination);
            high_resolution_clock::time_point finish = high_resolution_clock::now();
            duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
            
            //GETS ALL THE STATS FROM THE DFS ALGORITHM
            path = bfsIterative.returnPath();
            totalCost = bfsIterative.returnCost();
            averageCostMatrix[3] = averageCostMatrix[3] + totalCost;
            totalDistance = bfsIterative.returnDistance();
            averageDistanceMatrix[3] = averageDistanceMatrix[3] + totalDistance;
            numberOfExploredNodes = bfsIterative.returnExploredNodes();
            averageNodesMatrix[3] = averageNodesMatrix[3] + numberOfExploredNodes;
            executionTime = timeSpan.count();
            averageTimeMatrix[3] = averageTimeMatrix[3] + executionTime;
            iterativeOrRecursive = 0;
            stats();
            
            BFS bfsRecursive(graph.size(), graph, adjM);
            
            //CLOCKS THE SEARCH ALGORITHM
            high_resolution_clock::time_point start2 = high_resolution_clock::now();
            bfsRecursive.breadthFirstSearchRecursiveList(source, destination);
            high_resolution_clock::time_point finish2 = high_resolution_clock::now();
            duration<double> timeSpan2 = duration_cast<duration<double>>(finish2 - start2);
            
            //GETS ALL THE STATS FROM THE DFS ALGORITHM
            path = bfsRecursive.returnPath();
            totalCost = bfsRecursive.returnCost();
            averageCostMatrix[4] = averageCostMatrix[4] + totalCost;
            totalDistance = bfsRecursive.returnDistance();
            averageDistanceMatrix[4] = averageDistanceMatrix[4] + totalDistance;
            numberOfExploredNodes = bfsRecursive.returnExploredNodes();
            averageNodesMatrix[4] = averageNodesMatrix[4] + numberOfExploredNodes;
            executionTime = timeSpan2.count();
            averageTimeMatrix[4] = averageTimeMatrix[4] + executionTime;
            iterativeOrRecursive = 1;
        }
        else if(algorithmType == "DIJKSTRA")
        {
            Dijkstra dij(graph.size(), graph, adjM);
            //CLOCKS THE SEARCH ALGORITHM
            high_resolution_clock::time_point start = high_resolution_clock::now();
            dij.dijkstraSearchList(source, destination);
            high_resolution_clock::time_point finish = high_resolution_clock::now();
            duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
            
            
            path = dij.returnPath();
            totalCost = dij.returnCost();
            averageCostMatrix[5] = averageCostMatrix[5] + totalCost;
            totalDistance = dij.returnDistance();
            averageDistanceMatrix[5] = averageDistanceMatrix[5] + totalDistance;
            numberOfExploredNodes = dij.returnExploredNodes();
            averageNodesMatrix[5] = averageNodesMatrix[5] + numberOfExploredNodes;
            executionTime = timeSpan.count();
            averageTimeMatrix[5] = averageTimeMatrix[5] + executionTime;
        }
        else
        {
            AStar a(graph.size(), graph, adjM);
            //CLOCKS THE SEARCH ALGORITHM
            high_resolution_clock::time_point start = high_resolution_clock::now();
            a.aSearchMatrix(source, destination);
            high_resolution_clock::time_point finish = high_resolution_clock::now();
            duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
            
            
            path = a.returnPath();
            totalCost = a.returnCost();
            averageCostMatrix[6] = averageCostMatrix[6] + totalCost;
            totalDistance = a.returnDistance();
            averageDistanceMatrix[6] = averageDistanceMatrix[6] + totalDistance;
            numberOfExploredNodes = a.returnExploredNodes();
            averageNodesMatrix[6] = averageNodesMatrix[6] + numberOfExploredNodes;
            executionTime = timeSpan.count();
            averageTimeMatrix[6] = averageTimeMatrix[6] + executionTime;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SearchAlgorithms::stats()
{
    if(adj == "Adjacency List")
    {
        if(algorithmType == "DFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "*************\tADJACENCY LIST\t*************" << endl;
                cout << "*****\tDFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "*************\tADJACENCY LIST\t*************" << endl;
                cout << "*****\tDFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
        }
        else if (algorithmType == "BFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "*************\tADJACENCY LIST\t*************" << endl;
                cout << "*****\tBFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "*************\tADJACENCY LIST\t*************" << endl;
                cout << "*****\tBFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
        }
        else if(algorithmType == "DIJKSTRA")
        {
            //PRINTS ALL THE STATS
            cout << "*********************************************" << endl;
            cout << "*************\t ADJACENCY LIST\t*************" << endl;
            cout << "*******\t DIJKSTRA SEARCH ALGORITHM\t******" << endl;
            cout << "*********************************************" << endl;
            cout << "*********************************************\n" << endl;
            cout << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                cout << " -> ";
            }
            cout << "\n";
            cout << "Number of Nodes in Path: " << path.size() << endl;
            cout << "Total Cost of Path: " << totalCost << endl;
            cout << "Total Distance of Path: " << totalDistance << endl;
            cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            cout << "Execution Time of Path: " << executionTime << endl;
            cout << "\n\n\n";
        }
        else
        {
            //PRINTS ALL THE STATS
            cout << "*********************************************" << endl;
            cout << "************\t ADJACENCY LIST\t************" << endl;
            cout << "*********\t A* SEARCH ALGORITHM\t**********" << endl;
            cout << "*********************************************" << endl;
            cout << "*********************************************\n" << endl;
            cout << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                cout << " -> ";
            }
            cout << "\n";
            cout << "Number of Nodes in Path: " << path.size() << endl;
            cout << "Total Cost of Path: " << totalCost << endl;
            cout << "Total Distance of Path: " << totalDistance << endl;
            cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            cout << "Execution Time of Path: " << executionTime << endl;
            cout << "\n\n\n";
        }
    }
    else
    {
        if(algorithmType == "DFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "************\t ADJACENCY MATRIX\t************" << endl;
                cout << "*****\tDFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "************\t ADJACENCY MATRIX\t************" << endl;
                cout << "*****\tDFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
        }
        else if (algorithmType == "BFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "************\t ADJACENCY MATRIX\t************" << endl;
                cout << "*****\tBFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                cout << "*********************************************" << endl;
                cout << "************\t ADJACENCY MATRIX\t************" << endl;
                cout << "*****\tBFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                cout << "*********************************************" << endl;
                cout << "*********************************************\n" << endl;
                cout << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                cout << "\n";
                cout << "Number of Nodes in Path: " << path.size() << endl;
                cout << "Total Cost of Path: " << totalCost << endl;
                cout << "Total Distance of Path: " << totalDistance << endl;
                cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                cout << "Execution Time of Path: " << executionTime << endl;
                cout << "\n\n\n";
            }
        }
        else if(algorithmType == "DIJKSTRA")
        {
            //PRINTS ALL THE STATS
            cout << "*********************************************" << endl;
            cout << "************\t ADJACENCY MATRIX\t************" << endl;
            cout << "*******\t DIJKSTRA SEARCH ALGORITHM\t********" << endl;
            cout << "*********************************************" << endl;
            cout << "*********************************************\n" << endl;
            cout << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                cout << " -> ";
            }
            cout << "\n";
            cout << "Number of Nodes in Path: " << path.size() << endl;
            cout << "Total Cost of Path: " << totalCost << endl;
            cout << "Total Distance of Path: " << totalDistance << endl;
            cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            cout << "Execution Time of Path: " << executionTime << endl;
            cout << "\n\n\n";
        }
        else
        {
            //PRINTS ALL THE STATS
            cout << "*********************************************" << endl;
            cout << "************\t ADJACENCY MATRIX\t************" << endl;
            cout << "*********\t A* SEARCH ALGORITHM\t**********" << endl;
            cout << "*********************************************" << endl;
            cout << "*********************************************\n" << endl;
            cout << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                cout << " -> ";
            }
            cout << "\n";
            cout << "Number of Nodes in Path: " << path.size() << endl;
            cout << "Total Cost of Path: " << totalCost << endl;
            cout << "Total Distance of Path: " << totalDistance << endl;
            cout << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            cout << "Execution Time of Path: " << executionTime << endl;
            cout << "\n\n\n";
        }
    }
    
}

void SearchAlgorithms::save(int i)
{
    ofstream outFile ("/Users/dylanweeks/Downloads/outputFile.txt", ios::app);
    //OPENS AND WRITES SORTED DATA TO FILE
    
    
    if(adj == "Adjacency List")
    {
        if(algorithmType == "DFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "*************\tADJACENCY LIST\t*************" << endl;
                outFile << "*****\tDFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "*************\tADJACENCY LIST\t*************" << endl;
                outFile << "*****\tDFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    cout << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    cout << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
        }
        else if (algorithmType == "BFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "*************\tADJACENCY LIST\t*************" << endl;
                outFile << "*****\tBFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
               outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "*************\tADJACENCY LIST\t*************" << endl;
                outFile << "*****\tBFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
        }
        else if(algorithmType == "DIJKSTRA")
        {
            //PRINTS ALL THE STATS
            outFile << "*********************************************" << endl;
            outFile << "*************\t ADJACENCY LIST\t*************" << endl;
            outFile << "*******\t DIJKSTRA SEARCH ALGORITHM\t******" << endl;
            outFile << "*********************************************" << endl;
            outFile << "*********************************************\n" << endl;
            outFile << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                outFile << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                outFile << " -> ";
            }
            outFile << "\n";
            outFile << "Number of Nodes in Path: " << path.size() << endl;
            outFile << "Total Cost of Path: " << totalCost << endl;
            outFile << "Total Distance of Path: " << totalDistance << endl;
            outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            outFile << "Execution Time of Path: " << executionTime << endl;
            outFile << "\n\n\n";
        }
        else
        {
            //PRINTS ALL THE STATS
            outFile << "*********************************************" << endl;
            outFile << "************\t ADJACENCY LIST\t************" << endl;
            outFile << "*********\t A* SEARCH ALGORITHM\t**********" << endl;
            outFile << "*********************************************" << endl;
            outFile << "*********************************************\n" << endl;
            outFile << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                outFile << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                outFile << " -> ";
            }
            outFile << "\n";
            outFile << "Number of Nodes in Path: " << path.size() << endl;
            outFile << "Total Cost of Path: " << totalCost << endl;
            outFile << "Total Distance of Path: " << totalDistance << endl;
            outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            outFile << "Execution Time of Path: " << executionTime << endl;
            outFile << "\n\n\n";
        }
    }
    else
    {
        if(algorithmType == "DFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "************\t ADJACENCY MATRIX\t************" << endl;
                outFile << "*****\tDFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "************\t ADJACENCY MATRIX\t************" << endl;
                outFile << "*****\tDFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
        }
        else if (algorithmType == "BFS")
        {
            if(iterativeOrRecursive == 0)
            {
                //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "************\t ADJACENCY MATRIX\t************" << endl;
                outFile << "*****\tBFS ITERATIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
            else
            {
               //PRINTS ALL THE STATS
                outFile << "*********************************************" << endl;
                outFile << "************\t ADJACENCY MATRIX\t************" << endl;
                outFile << "*****\tBFS RECURSIVE SEARCH ALGORITHM\t*****" << endl;
                outFile << "*********************************************" << endl;
                outFile << "*********************************************\n" << endl;
                outFile << "PATH: ";
                for(int i = 0; i < path.size(); i++)
                {
                    outFile << path[i];
                    if(i == path.size() - 1)
                    {
                        break;
                    }
                    outFile << " -> ";
                }
                outFile << "\n";
                outFile << "Number of Nodes in Path: " << path.size() << endl;
                outFile << "Total Cost of Path: " << totalCost << endl;
                outFile << "Total Distance of Path: " << totalDistance << endl;
                outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
                outFile << "Execution Time of Path: " << executionTime << endl;
                outFile << "\n\n\n";
            }
        }
        else if(algorithmType == "DIJKSTRA")
        {
            //PRINTS ALL THE STATS
            outFile << "*********************************************" << endl;
            outFile << "************\t ADJACENCY MATRIX\t************" << endl;
            outFile << "*******\t DIJKSTRA SEARCH ALGORITHM\t********" << endl;
            outFile << "*********************************************" << endl;
            outFile << "*********************************************\n" << endl;
            outFile << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                outFile << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                outFile << " -> ";
            }
            outFile << "\n";
            outFile << "Number of Nodes in Path: " << path.size() << endl;
            outFile << "Total Cost of Path: " << totalCost << endl;
            outFile << "Total Distance of Path: " << totalDistance << endl;
            outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            outFile << "Execution Time of Path: " << executionTime << endl;
            outFile << "\n\n\n";
        }
        else
        {
            //PRINTS ALL THE STATS
            outFile << "*********************************************" << endl;
            outFile << "************\t ADJACENCY MATRIX\t************" << endl;
            outFile << "*********\t A* SEARCH ALGORITHM\t**********" << endl;
            outFile << "*********************************************" << endl;
            outFile << "*********************************************\n" << endl;
            outFile << "PATH: ";
            for(int i = 0; i < path.size(); i++)
            {
                outFile << path[i];
                if(i == path.size() - 1)
                {
                    break;
                }
                outFile << " -> ";
            }
            outFile << "\n";
            outFile << "Number of Nodes in Path: " << path.size() << endl;
            outFile << "Total Cost of Path: " << totalCost << endl;
            outFile << "Total Distance of Path: " << totalDistance << endl;
            outFile << "Total Number of Explored Nodes: " << numberOfExploredNodes << endl;
            outFile << "Execution Time of Path: " << executionTime << endl;
            outFile << "\n\n\n";
        }
    }
    
    
    if(i == 99)
    {
        outFile << "*********************************" << endl;
        outFile << "*********************************" << endl;
        outFile << "*********************************" << endl;
        outFile << "*********************************" << endl;
        outFile << "*********************************" << endl;
        
        outFile << "AVERAGE RESULTS ADJACENCY LIST:" << endl;
        outFile << "DFS ITREATIVE | NODES IN PATH = " << averageNodesList[1]/100 << " | NODES EXPLORED = " << averageExploredList[1]/100 << " | TIME = " << averageTimeList[1]/100 << " | DISTANCE = " << averageDistanceList[1]/100 << "\n" << endl;
        outFile << "DFS RECURSIVE | NODES IN PATH = " << averageNodesList[2]/100 << " | NODES EXPLORED = " << averageExploredList[2]/100 << " | TIME = " << averageTimeList[2]/100 << " | DISTANCE = " << averageDistanceList[2]/100 << "\n" << endl;
        outFile << "BFS ITERATUVE | NODES IN PATH = " << averageNodesList[3]/100 << " | NODES EXPLORED = " << averageExploredList[3]/100 << " | TIME = " << averageTimeList[3]/100 << " | DISTANCE = " << averageDistanceList[3]/100 << "\n" << endl;
        outFile << "BFS RECURSIVE | NODES IN PATH = " << averageNodesList[4]/100 << " | NODES EXPLORED = " << averageExploredList[4]/100 << " | TIME = " << averageTimeList[4]/100 << " | DISTANCE = " << averageDistanceList[4]/100 << "\n" << endl;
        outFile << "DIJKSTRA | NODES IN PATH = " << averageNodesList[5]/100 << " | NODES EXPLORED = " << averageExploredList[5]/100 << " | TIME = " << averageTimeList[5]/100 << " | DISTANCE = " << averageDistanceList[5]/100 << "\n" << endl;
        outFile << "A* | NODES IN PATH = " << averageNodesList[6]/100 << " | NODES EXPLORED = " << averageExploredList[6]/100 << " | TIME = " << averageTimeList[6]/100 << " | DISTANCE = " << averageDistanceList[6]/100 << "\n" << endl;
        
        outFile << "AVERAGE RESULTS ADJACENCY MATRIX:" << endl;
        outFile << "DFS ITREATIVE | NODES IN PATH = " << averageNodesMatrix[1]/100 << " | NODES EXPLORED = " << averageExploredMatrix[1]/100 << " | TIME = " << averageTimeMatrix[1]/100 << " | DISTANCE = " << averageDistanceMatrix[1]/100 << "\n" << endl;
        outFile << "DFS RECURSIVE | NODES IN PATH = " << averageNodesMatrix[2]/100 << " | NODES EXPLORED = " << averageExploredMatrix[2]/100 << " | TIME = " << averageTimeMatrix[2]/100 << " | DISTANCE = " << averageDistanceMatrix[2]/100 << "\n" << endl;
        outFile << "BFS ITERATUVE | NODES IN PATH = " << averageNodesMatrix[3]/100 << " | NODES EXPLORED = " << averageExploredMatrix[3]/100 << " | TIME = " << averageTimeMatrix[3]/100 << " | DISTANCE = " << averageDistanceMatrix[3]/100 << "\n" << endl;
        outFile << "BFS RECURSIVE | NODES IN PATH = " << averageNodesMatrix[4]/100 << " | NODES EXPLORED = " << averageExploredMatrix[4]/100 << " | TIME = " << averageTimeMatrix[4]/100 << " | DISTANCE = " << averageDistanceMatrix[4]/100 << "\n" << endl;
        outFile << "DIJKSTRA | NODES IN PATH = " << averageNodesMatrix[5]/100 << " | NODES EXPLORED = " << averageExploredMatrix[5]/100 << " | TIME = " << averageTimeMatrix[5]/100 << " | DISTANCE = " << averageDistanceMatrix[5]/100 << "\n" << endl;
        outFile << "A* | NODES IN PATH = " << averageNodesMatrix[6]/100 << " | NODES EXPLORED = " << averageExploredMatrix[6]/100 << " | TIME = " << averageTimeMatrix[6]/100 << " | DISTANCE = " << averageDistanceMatrix[6]/100 << "\n" << endl;
    }
    
    outFile.close();

}
