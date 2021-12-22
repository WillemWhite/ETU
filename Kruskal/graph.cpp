#include <iostream>
#include <limits>
#include "vector.h"
#include "graph.h"
#include "DSU.h"


Graph::Graph(const Graph& other)
    :verSize(other.verSize) {
    this->arrOfEdges = other.arrOfEdges;
    this->vertexUnion = other.vertexUnion;
}

void Graph::inputEdge(Edge& edge) {
    char vertex1 = NULL, vertex2 = NULL;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        char c = std::cin.get();
        if (c == ' ') continue;
        if (c == '\n') break;
        vertex1 = c;
        break;
    } while (true);

    do {
        char c = std::cin.get();
        if (c == ' ') continue;
        if (c == '\n') break;
        vertex2 = c;
        break;
    } while (true);

    int weight; std::cin >> weight;
    edge = { vertex1, vertex2, weight };

    int count1 = 0, count2 = 0;
    while (count1 < this->vertexUnion.getSize()) {
        if (edge.vertex1 != this->vertexUnion.getArrPtr()[count1].memb) {
            count1++;
            continue;
        }
        break;
    }
    while (count2 < this->vertexUnion.getSize()) {
        if (edge.vertex2 != this->vertexUnion.getArrPtr()[count2].memb) {
            count2++;
            continue;
        }
        break;
    }
    if (count1 == this->vertexUnion.getSize()) {
        this->vertexUnion.makeSet(edge.vertex1);
        if (count2 == this->vertexUnion.getSize() - 1)
            this->vertexUnion.makeSet(edge.vertex2);
    }
    if (count2 == this->vertexUnion.getSize())this->vertexUnion.makeSet(edge.vertex2);

    this->verSize = this->vertexUnion.getSize();
}

void Graph::input() {
    std::cout << "Please, enter number of your edges: ";
    int n; std::cin >> n;
    std::cout << std::endl << "Please, enter your edges: " << std::endl;
    for (int i = 0; i < n; i++) {
        Edge edge; this->inputEdge(edge);
        this->addEdge(edge);
    }
    std::cout << std::endl << "Thanks!" << std::endl;
}

void Graph::outputEdge(const int i) {
    if (i > this->arrOfEdges.getSize())
        return;
    Edge edge = *this->arrOfEdges.take(i);
    std::cout << edge.vertex1 << " " << edge.vertex2 << " " << edge.weight << std::endl;
}

void Graph::output() {
    if (!this->arrOfEdges.getArrPtr())
        return;
    for (int i = 0; i < this->arrOfEdges.getSize(); i++)
        this->outputEdge(i);
}

//Insert sort
void Graph::sortEdge() {
    if (this->verSize <= 1)
        return;
    for (int j = 1; j < this->arrOfEdges.getSize(); j++)
    {
        Edge edge = this->arrOfEdges.getArrPtr()[j];
        int i = j - 1;
        while (i >= 0 && this->arrOfEdges.getArrPtr()[i].weight > edge.weight)
        {
            this->arrOfEdges.getArrPtr()[i + 1] = this->arrOfEdges.getArrPtr()[i--];
        }
        this->arrOfEdges.getArrPtr()[i + 1] = edge;
    }
}

bool Graph::isCycle(const Edge& edge) {
    if (this->vertexUnion.find(edge.vertex1) == this->vertexUnion.find(edge.vertex2))
        return true;
    else return false;
}

void Graph::operator=(const Graph& other) {
    this->verSize = other.verSize;
    this->arrOfEdges = other.arrOfEdges;
    this->vertexUnion = other.vertexUnion;
}

void Graph::MST(Graph& MST) {
    this->sortEdge();
    *MST.getVertexUnion() = *this->getVertexUnion();
    MST.verSize = this->verSize;

    if (this->getArrOfEdges()->getSize() >= 1) {
        MST.addEdge(*this->getArrOfEdges()->take(0));
        MST.getVertexUnion()->makeUnion(
            MST.getVertexUnion()->find(this->getArrOfEdges()->take(0)->vertex1),
            MST.getVertexUnion()->find(this->getArrOfEdges()->take(0)->vertex2));

        for (int i = 1; i < this->getArrOfEdges()->getSize(); i++) {

            if (!MST.isCycle(*this->getArrOfEdges()->take(i))) {
                MST.addEdge(*this->getArrOfEdges()->take(i));
                MST.getVertexUnion()->makeUnion(
                    MST.getVertexUnion()->find(this->getArrOfEdges()->take(i)->vertex1),
                    MST.getVertexUnion()->find(this->getArrOfEdges()->take(i)->vertex2));
            }
        }
    }
}

int Graph::MSTweight() {
    int weight = 0;
    for (int i = 0; i < this->arrOfEdges.getSize(); i++)
        weight += this->arrOfEdges.take(i)->weight;
    return weight;
}

void Graph::MSToutput() {
    if (this->verSize <= 1)
        return;
    //sorting vertex1
    for (int j = 1; j < this->arrOfEdges.getSize(); j++)
    {
        Edge edge = this->arrOfEdges.getArrPtr()[j];
        int i = j - 1;

        while (i >= 0 && this->arrOfEdges.getArrPtr()[i].vertex1 > edge.vertex1)
            this->arrOfEdges.getArrPtr()[i + 1] = this->arrOfEdges.getArrPtr()[i--];

        this->arrOfEdges.getArrPtr()[i + 1] = edge;
    }
    //sorting vertex2
    int counter = 0;
    while (counter < this->arrOfEdges.getSize() - 1) {

        int begin = counter;
        while (this->arrOfEdges.take(counter)->vertex1 ==
            this->arrOfEdges.take(counter + 1)->vertex1)
            counter++;
        counter++;

        for (int j = begin + 1; j < counter; j++) {
            Edge edge = this->arrOfEdges.getArrPtr()[j];

            int i = j - 1;
            while (i >= 0 && this->arrOfEdges.getArrPtr()[i].vertex2 > edge.vertex2)
                this->arrOfEdges.getArrPtr()[i + 1] = this->arrOfEdges.getArrPtr()[i--];

            this->arrOfEdges.getArrPtr()[i + 1] = edge;
        }
    }
    //print
    for (int i = 0; i < this->arrOfEdges.getSize(); i++) {
        Edge edge = *this->arrOfEdges.take(i);
        std::cout << edge.vertex1 << " " << edge.vertex2 << std::endl;
    }
    std::cout << this->MSTweight() << std::endl;
}

