#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2, int distance){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = distance;
                    vertices[i].adj.push_back(av);
                    /*
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = distance;
                    vertices[j].adj.push_back(av2);
                    */
                }
            }
        }
    }
}
void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        vertices.push_back(v);
    }
}

int Graph::isAdjacent(std::string v1, std::string v2){
    bool status = false;
    for (int i = 0; i < vertices.size(); i++){
        if (vertices[i].name == v1){
            for (int j = 0; j < vertices[i].adj.size(); j++){
                if (vertices[i].adj[j].v->name == v2){
                    status = true;
                }
            }
        }
    }
    if (status == false){
        return 0;
    }
    else{
        return 1;
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1){
                cout << "***";
            }
        }
        cout<<endl;
    }

}
