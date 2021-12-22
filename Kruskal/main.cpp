#include <iostream>
#include <ctime>
#include "vector.h"
#include "graph.h"
#include "DSU.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graph graph;
    graph.input();
    cout << endl << "Your edges: " << endl;
    graph.output();

    Graph MST;
    graph.MST(MST);
    cout << endl << "MST edges of this graph: " << endl;
    MST.output();


    cout << endl << "Disjoint Set Union of this MST: " << endl;
    MST.getVertexUnion()->output();

    cout << endl << "MST Output: " << endl;
    MST.MSToutput();

    system("pause");
    return 0;
}