// Dynamic Memeory Allocation
// Read text file and store it in dynamically allocated array
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void resize(int * oldArray, int * capacity){
	int newCapacity = *capacity * 2;
	int * newArray = new int[newCapacity];
	for (int i=0; i < *capacity; i++){
		newArray[i] = oldArray[i];
	}
	delete[] oldArray;
	oldArray = newArray;
	*capacity = newCapacity;
}


int main(int argc, char* argv[]){
	ifstream inFile;
	inFile.open(argv[1]);
	int capacity = 10;
	int * p = new int[capacity];
	if (!p){
		cout << "error" << endl;
		return -1;
	}
	string data;
	int numElement = 0;
	if (inFile.is_open()){
		while (getline(inFile, data)){
			int newNumber = stoi(data);
			if (numElement == capacity){
				resize(p, &capacity);
				cout << "increase capacity!" << endl;
			}
			p[numElement] = newNumber;
			cout << newNumber << endl;
			numElement++;
		}
	}
	cout << "size of array:" << capacity << endl;
	cout << "total number of elements:" << numElement << endl;
	delete[] p;
	return 0;
}