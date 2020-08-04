//Dylan Weeks, 9/12/19, 47343235, CSE 3353
#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>
#include <fstream>

using namespace std;

class Algorithms
{
    
public:
    //USES STRATEGY CLASS (PURE VIRTUAL FUNCTIONS)
    virtual void load(char* argv[]) = 0;
    virtual void select(int algorithm, int adjType) = 0;
    virtual void execute() = 0;
    virtual void stats() = 0;
    virtual void save(int i) = 0;
};


#endif /* ALGORITHMS_H */


