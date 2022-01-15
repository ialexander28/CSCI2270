#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
};

struct vertex{
    std::string name;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2);
        void addVertex(std::string name);
	bool ifPathExistsLessThanDist(string vertex1, string vertex2, int dist);
    protected:
    private:
        std::vector<vertex> vertices;

};

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
void Graph::addEdge(string v1, string v2){

    for(int i = 0; i < (int)vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < (int)vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < (int)vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            //cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
		v.visited = false;
        vertices.push_back(v);

    }
}

bool Graph::ifPathExistsLessThanDist(string vertex1, string vertex2, int dist){
	unsigned int k=0;
    vertex* src;
    int path = 0;
    queue<vertex*> vQ;
    bool vertexFound = false;
    while (k < vertices.size()) {
        if (vertices[k].name == vertex1) {
            src = &vertices[k];
            break;
        }
        k++;
    }
    if (src){
    	src->visited = true;
        src->distance = 0;
        bool found = false;
        vQ.push(src);
        while(vQ.size() != 0 && !found){
        	vertex* curV = vQ.front();
            vQ.pop();
            for(unsigned int i=0; i<curV->adj.size(); i++) {
            	if (!curV->adj[i].v->visited){
            		curV->adj[i].v->distance = curV->distance + 1;
            		if (curV->adj[i].v->name == vertex2){
            			found = true;
            			path = curV->adj[i].v->distance;
            			vertexFound = true;
            			break;
            		}
            		else {
            			curV->adj[i].v->visited = true;
            			vQ.push(curV->adj[i].v);
            		}
            	}
            }
            if(found) {
                break;
            }
        }
    }
    if (path < dist && vertexFound){
    	return true;
    }
    else {
    	return false;
    }

}

int main() {
    Graph g;

    g.addVertex("a");
    g.addVertex("b");
    g.addVertex("c");
    g.addVertex("d");
    g.addVertex("e");
    g.addVertex("g");

    g.addEdge("a", "b");
    g.addEdge("a", "d");
    g.addEdge("c", "d");
    g.addEdge("b", "c");
    g.addEdge("d", "e");
    g.addEdge("c", "e");

    cout << g.ifPathExistsLessThanDist("a", "g", 3) << endl;;

    return 0;
}
