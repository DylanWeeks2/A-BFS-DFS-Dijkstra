//DYLAN WEEKS, 47343235, 10/17/19
#include <iostream>
#include "Algortithms.h"
#include "SearchAlgorithms.h"

int main(int argc, char** argv)
{

    Algorithms* Search = new SearchAlgorithms();
    Search -> load(argv);
    
    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            Search -> select(i, j);
            Search -> execute();
            Search -> stats();
        }

    }
    
    //THIS FOR LOOP IS TO DO THE LAB REPORT TEST OF 100 TRIALS
    for(int i = 0; i < 100; i++)
    {
        Search -> load(argv);
        for(int j = 0; j < 2; j++)
        {
            for(int x = 0; x < 3; x++)
            {
                Search -> select(x, j);
                Search -> execute();
                Search -> save(i);
            }

        }
    }
    return 0;
};

