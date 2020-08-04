#ifndef ADJLIST_H
#define ADJLIST_H
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class AdjList
{
public:
    int position1,position2,position3;
    double d = sqrt((position1 * position1) + (position2*position2) + (position3 * position3));
    list<pair<int, int>> weights;
    vector<int> connectingNodes;
    map<int,int> connectionWeight;
};

#endif // ADJLIST_H
