#include <vector>
#include <iostream>
#include




void Graph::assignDistricts()
{
    int districtID = 1;
    for (int i=0; i < vertices.size(); i++){
        if (vertices[i].visited == false){
            DFSLabel(vertices[i].name, districtID);
            districtID++;
        }
    }
}

void Graph::DFSLabel(string startingCity, int distID)
{
    vertex * startVertex = findVertex(startingCity);
    stack<vertex *> sVertex;
    if (startVertex){
        sVertex.push(startVertex);
        while (!sVertex.empty()){
            vertex * curV = sVertex.top();
            sVertex.pop();
            if (!curV->visited){
                curV->districtID = distID;
                curV->visited = true;
            }
            for (int i=0; i < curV->adj.size(); i++){
                if (!curV->adj[i].v->visited)
                    sVertex.push(curV->adj[i].v);
            }
        }
    }
}

void Graph::shortestPath(string startingCity, string endingCity){
    vertex * startVertex = findVertex(startingCity);
    vertex * endVertex = findVertex(endingCity);
    for (int i=0; i < vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].unweightedDistance = INT_MAX;
    }
    if (startVertex == nullptr || endVertex == nullptr){
        cout << "One or more cities doesn't exist" << endl;
    }
    else if (startVertex->districtID != endVertex->districtID){
        cout << "No safe path between cities" << endl;
    }
    else if (startVertex->districtID == -1 || endVertex->districtID == -1){
        cout << "Please identify the districts before checking distance" << endl;
    }
    else {
        vertex * parentPrev;
        vertex * parent;
        int dist = 0;
        queue<vertex *> vertexQ;
        stack<vertex *> path;
        startVertex->visited = true;
        startVertex->parent = nullptr;
        startVertex->unweightedDistance = dist;
        vertexQ.push(startVertex);
        while (vertexQ.size() != 0){
            vertex * curV = vertexQ.front();
            vertexQ.pop();
            if (curV->parent == nullptr || curV->parent != parentPrev){
                dist++;
            }
            parentPrev = curV->parent;
            for (int i=0; i < curV->adj.size(); i++){
                if (!curV->adj[i].v->visited){
                    curV->adj[i].v->parent = curV;
                    parent = curV;
                    curV->adj[i].v->unweightedDistance = dist;
                    curV->adj[i].v->visited = true;
                    vertexQ.push(curV->adj[i].v);
                    if (curV->adj[i].v == endVertex){
                        cout << dist << ", ";
                        while (parent != nullptr){
                            path.push(parent);
                            parent = parent->parent;
                        }
                        while (path.size() != 0){
                            vertex * temp = path.top();
                            path.pop();
                            cout << temp->name << ", ";
                        }
                        cout << curV->adj[i].v->name << endl;
                    }
                }
            }
        }
    }
}