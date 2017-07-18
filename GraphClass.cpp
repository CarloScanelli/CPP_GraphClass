#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

#include "GraphClass.hpp"


using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout << vertices[i].name << endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);
    }
}

void Graph::addEdge(string v1, string v2, int weight)
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].districtID << ":" << vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout << vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1){
                cout << "***";}
        }
        cout << endl;
    }
}

void Graph::findDistrict()
{
    int current = 1;
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].districtID == -1){
            BFTraversal(vertices[i], current);
            current++;
        }
    }
}

void Graph::BFTraversal(vertex startingCity, int counter)
{
    queue<vertex*> bfq;
    vertex v = startingCity;
    int i = 0;
    bfq.push(&startingCity);
    startingCity.districtID = counter;
    while (!bfq.empty()){
        v = *bfq.front();
        bfq.pop();
        for(i=0; i<v.adj.size(); i++){
            if (v.adj[i].v->districtID == -1){
                bfq.push(v.adj[i].v);
                v.adj[i].v->districtID = counter;
            }
        }
    }
}

void Graph::shortestPath(string startingCity, string endingCity)
{
    int startingCityID = 0;
    int endingCityID = 0;

    for (int i=0; i<vertices.size(); i++){
        if (vertices[i].name == startingCity)
        {
            startingCityID = vertices[i].districtID;
        }
    }
    for (int i=0; i<vertices.size(); i++){
        if (vertices[i].name == endingCity)
        {
            endingCityID = vertices[i].districtID;
        }
    }

    if (startingCityID != endingCityID)
    {
        cout << "No safe path between cities" << endl;

    }

    else if (vertices[1].districtID == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
    }

    else{
        queue<vertex*> bfq;
        vector<vertex*> cities;
        vertex* v;
        int i = 0;
        for (i=0; i<vertices.size(); i++){
            vertices[i].visited = false;
        }
        for (i=0; i<vertices.size(); i++){
            if (startingCity == vertices[i].name){
                v = &vertices[i];
                v->visited = true;
                v->distance = 0;
                bfq.push(&vertices[i]);
                break;
            }
        }
        bool safePath = false;
        while (!bfq.empty())
        {
            v = bfq.front();
            bfq.pop();
            for (i=0; i<v->adj.size(); i++)
            {
                if (v->adj[i].v->visited == false)
                {
                    v->adj[i].v->distance = v->distance + 1;
                    v->adj[i].v->visited = true;
                    bfq.push(v->adj[i].v);
                    v->adj[i].v->previous = v;
                    if (v->adj[i].v->name == endingCity)
                    {
                        endingCityID = v->adj[i].v->districtID;
                        vertex *z = v->adj[i].v;
                        cout << v->adj[i].v->distance << ",";
                        while (z != NULL)
                        {
                            cities.push_back(z);
                            z = z->previous;
                        }
                    }
                }
            }
        }
        cout << cities[cities.size()-1]->name;
        for (int i = cities.size() - 2; i>=0; i--)
        {
           cout << "," << cities[i]->name;
        }
        cout << endl;
    }
}

void Graph::Dijkstra(string starting, string destination)
{

    int startingCityID = 0;
    int endingCityID = 0;

    for (int i=0; i<vertices.size(); i++){
        if (vertices[i].name == starting)
        {
            startingCityID = vertices[i].districtID;
        }
    }
    for (int i=0; i<vertices.size(); i++){
        if (vertices[i].name == destination)
        {
            endingCityID = vertices[i].districtID;
        }
    }

    if (startingCityID != endingCityID)
    {
        cout << "No safe path between cities" << endl;

    }

    else if (vertices[1].districtID == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
    }
    else{
    std::vector<vertex*> solved;
    vertex *s;
    vertex *d;

    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == starting){
            s = &vertices[i];
    }
        if(vertices[i].name == destination)
        {
            d = &vertices[i];
        }
    }

    s->visited = true;
    s->distance = 0;
    solved.push_back(s);

    // loop through until shortest path is found
    while (d->visited == false)
    {
        vertex *minVertex;
        int minDistance = INT_MAX;

        for (int i = 0; i < solved.size(); i++) {
            for (int j = 0; j < solved[i]->adj.size(); j++) {
                if (solved[i]->adj[j].v->visited == false) {
                    int dist = solved[i]->distance + solved[i]->adj[j].weight;
                    if (dist < minDistance) {
                        minDistance = dist;
                        minVertex = solved[i]->adj[j].v;
                        minVertex->distance = minDistance;
                        minVertex->previous = solved[i];
                    }
                }
            }
        }

        minVertex->visited = true;
        solved.push_back(minVertex);
    }

    vertex *temp = solved.back();
    vector<vertex> path;
    while(temp != NULL)
    {
        path.push_back(*temp);
        temp = temp->previous;
    }

    //cout << "Shortest Path" << endl;
    cout << solved.back()->distance << ",";
    for(int j = path.size() - 1; j >= 0; j--)
    {
        if(path[j].name == starting)
        {
        cout << path[j].name;
        }

        else
        {
            cout << "," << path[j].name;
        }
    }
    cout << endl;
    //cout << "Minimum Distance: " << solved.back()->distance << endl;
    }
}
