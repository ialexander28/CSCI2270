#include "Graph.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(){
	Graph city;
	std::vector<std::vector<std::string>> matrix;
	ifstream inFile("mat.txt");
	std::string data;
	while(getline(inFile, data)){
		stringstream ss(data);
		std::vector<std::string> tempv;
		std::string current;
		while(ss >> current){
			tempv.push_back(current);
		}
		matrix.push_back(tempv);
	}
	for (int i = 1; i < 5; i++){
		city.addVertex(matrix[i][0]);
	}
	for (int j = 2; j < 5; j++){
		city.addEdge(matrix[1][0],matrix[0][j],stoi(matrix[1][j]));
	}
	for (int k = 3; k < 5; k++){
		city.addEdge(matrix[2][0],matrix[0][k],stoi(matrix[2][k]));
	}
	for (int l = 4; l < 5; l++){
		city.addEdge(matrix[3][0],matrix[0][l],stoi(matrix[2][l]));
	}
	city.displayEdges();
}
