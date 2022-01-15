#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"
using namespace std;

void printMenu(){
	cout << "======Main Menu======" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Rent a movie" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Delete a movie" << endl;
	cout << "5. Count the movies" << endl;
	cout << "6. Quit" << endl;
}

int main(int argc, char * argv[]){
	ifstream inFile;
	inFile.open(argv[1]);
	string userInput;
	MovieTree movies;
	string movieName, data, title, ranking, year, quantity;
	if (inFile.is_open()){
		while(getline(inFile, data)){
			stringstream ss(data);
			getline(ss, ranking, ',');
			getline(ss, title, ',');
			getline(ss, year, ',');
			getline(ss, quantity, ',');
			movies.addMovieNode(stoi(ranking), title, stoi(year), stoi(quantity));
		}
		inFile.close();
	}
	while (userInput != "6"){
		printMenu();
		getline(cin, userInput);
		if (userInput == "1"){
			cout << "Enter title: " << endl;
			getline(cin, movieName);
			movies.findMovie(movieName);
		}
		else if (userInput == "2"){
			cout << "Enter title: " << endl;
			getline(cin, movieName);
			movies.rentMovie(movieName);
		}
		else if (userInput == "3"){
			movies.printMovieInventory();
		}
		else if (userInput == "4"){
			cout << "Enter title: " << endl;
			getline(cin, movieName);
			movies.deleteMovieNode(movieName);
		}
		else if (userInput == "5"){
			cout << "Tree contains: " << movies.countMovieNodes() << " movies." << endl;
		}
		else if (userInput == "6"){
			cout << "Goodbye!" << endl;
			return 0;
		}
		else {
			cout << "Invalid input!" << endl;
		}
	}
	return 0;
}
