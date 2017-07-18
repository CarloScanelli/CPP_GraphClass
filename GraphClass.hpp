#ifndef _GRAPH_CLASS_
#define _GRAPH_CLASS_

#include <vector>
#include <iostream>
#include <queue>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;

    bool visited = false;
    int distance;
    vertex *previous = NULL;
    std::vector<adjVertex> adj;
    int districtID = -1;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void findDistrict();
        void BFTraversal(vertex, int);
        void shortestPath(std::string city1, std::string city2);
        void Dijkstra(std::string starting, std::string destination);
    protected:
    private:
        std::vector<vertex> vertices;
};

#endif
