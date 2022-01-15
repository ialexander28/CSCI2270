#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// define car struct
struct CarData {
	string model;
	string make;
	string year;
};

int main (int argc, char* argv[]){
	int length = std::stoi(argv[2]);
	CarData carArray[length];
	ifstream inFile;
	ofstream outFile;
	string data;
	inFile.open(argv[1]); // opens input and output file
	if (inFile.is_open()){
		cout << "opened successfully" << endl;
		for (int i=0; i < length; i++) {
			getline(inFile, data);	
			stringstream ss(data);
			getline(ss, carArray[i].model, ' ');
			getline(ss, carArray[i].make, ' ');
			getline(ss, carArray[i].year, ' ');
			outFile << "model: " << carArray[i].model << '\t';
			outFile << "make: " << carArray[i].make << '\t';
			outFile << "year: " << carArray[i].year << endl;
			size++
		}
		inFile.close();
	}
	else {
		cout << "file unsuccessfully opened" << endl;
	}
	return 0;
}