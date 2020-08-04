#ifndef AdjMatrix_h
#define AdjMatrix_h

class AdjMatrix
{
public:
    int** matrix;
    int totalVertex;
    int totalNodes;
    vector<int> p1,p2,p3;
    map<int,int> connectionWeight;
    
    void setValues(int countV, int countN)
    {
        totalVertex = countV;
        totalNodes = countN;
        
        matrix = new int*[totalVertex];
        for (int row = 1; row <= totalVertex; row++)
        {
            matrix[row] = new int[totalVertex];
            
            for (int column = 1; column <= totalVertex; column++)
            {
                matrix[row][column] = 0;
            }
        }
    }

    void insert(int vertex, int node, int weight)
    {
        matrix[vertex][node] = weight;
        matrix[vertex][node] = weight;
    }
    
};

#endif /* AdjMatrix_h */
