#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void printMenu(){
    cout << "======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Vertex adjacent" << endl;
    cout << "3. Quit" << endl;
}

int main(int argc, char * argv[]){
    Graph city;
    std::vector<std::vector<std::string>> matrix;
    ifstream inFile(argv[1]);
    std::string data;
    while(getline(inFile, data)){
        stringstream ss(data);
        std::vector<std::string> tempv;
        std::string current;
        while(getline(ss, current, ',')){
            tempv.push_back(current);
        }
        matrix.push_back(tempv);
    }
    for (int i = 1; i < 16; i++){
        city.addVertex(matrix[i][0]);
    }
    int j = 0;
    int k = 1;
    while (k != 16){
        for (j = 1; j < 16; j++){
            if (stoi(matrix[j][k]) != -1) {
                city.addEdge(matrix[k][0],matrix[0][j],stoi(matrix[k][j]));
            }
        }
        k++;
    }
    string userInput, cityName, cityName2;
    while (userInput != "3"){
        printMenu();
        getline(cin, userInput);
        if (userInput == "1"){
            city.displayEdges();
        }
        else if (userInput == "2"){
            cout << "Enter first city:" << endl;
            getline(cin, cityName);
            cout << "Enter second city:" << endl;
            getline(cin, cityName2);
            if (city.isAdjacent(cityName,cityName2)){
                cout << "True" << endl;
            }
            else{
                cout << "False" << endl;
            }
        }
        else if (userInput == "3"){
            cout << "Goodbye!" << endl;
            return 0;
        }
        else{
            cout << "Invalid input!" << endl;
        }
    }
}