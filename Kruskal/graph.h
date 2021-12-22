#ifndef GRAPH_H
#define GRAPH_H
#include "vector.h"
#include "DSU.h"

class Edge {
public:
    char vertex1;
    char vertex2;
    int weight = 0;

    Edge() { vertex1 = NULL, vertex2 = NULL; weight = NULL; }
    Edge(char vertex1Arg, char vertex2Arg, int weightArg) {
        vertex1 = vertex1Arg; vertex2 = vertex2Arg; weight = weightArg;
    }
};

class Graph {
private:
    int verSize = 0;
    Vector<Edge> arrOfEdges;
    DSU<char> vertexUnion;

public:
    Graph(const Graph&);
    Graph() { this->verSize = 0; this->arrOfEdges; }
    ~Graph() { this->verSize = 0; }

public:
    void addEdge(Edge& edge) { this->arrOfEdges.add(edge, 0); }
    void inputEdge(Edge&);
    void input();
    void outputEdge(const int i);
    void output();
    void sortEdge();
    bool isCycle(const Edge& edge);
    int getVerSize() { return this->verSize; }
    DSU<char>* getVertexUnion() { return &this->vertexUnion; }
    Vector<Edge>* getArrOfEdges() { return &this->arrOfEdges; }
    void operator = (const Graph& other);
    void MST(Graph&);
    int MSTweight();
    void MSToutput();
};

#endif //GRAPH_H