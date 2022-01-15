// Name: Guanxiong Fu
// Assignment 1
// Instructor: Jason Zietz

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// define sale struct
struct item {
	string type;	 // bike, microwave, dresser, truck, or chicken
	string category; // either for sale or wanted
	string price; 	 // price of the item
};

// check if items are matched
bool match(item currentItem, item arrayItem);

// compare the prices of matched items and return the for sale price
string comparePrice(item currentItem, item arrayItem);


int main(int argc, char* argv[]){
	item itemArray[100];			// allocate an array of items, maximum size is 100
	ifstream inFile;				// garageSale.txt
	inFile.open(argv[1]);		    // opens input and output file 
	int numArrayItems = 0;			// unsold items in array
	int numSold = 0;				// sold items
	int matchStatus = 0;			// 1 if matched, 0 if not
	string data;
	if (inFile.is_open()){															// when file is opened
		while (getline(inFile, data)){												// parse until end of file
			stringstream ss(data);
			item currentItem;
			getline(ss, currentItem.type, ',');										// get the important information from each line
			getline(ss, currentItem.category, ',');
			getline(ss, currentItem.price, ',');
			for (int i=0; i < numArrayItems; i++){									// iterate through the array to see if there is a match
				if (match(currentItem, itemArray[i]) == true){
					currentItem.price = comparePrice(currentItem, itemArray[i]);	// save the price of for sale items
					cout << currentItem.type << " " << currentItem.price << endl;	// print out sold items and the price
					for (int j=i; j < (numArrayItems-2); j++){						// delete sold item from array and shift array
						itemArray[j] = itemArray[j+1];
					} 
					matchStatus = 1;
					numArrayItems--;
					numSold++;
					break;
				}
				else {
					matchStatus = 0;
				}
			}
			if (!matchStatus){														// add item to array if there's no match
				itemArray[numArrayItems].type = currentItem.type;
				itemArray[numArrayItems].category = currentItem.category;
				itemArray[numArrayItems].price = currentItem.price;
				numArrayItems++;
			}
		}
		inFile.close();
	}
	cout << numSold << endl;														// print number of items sold
	for (int i=0; i < numArrayItems; i++){											// print all unsold items
		cout << itemArray[i].type << ", ";
		cout << itemArray[i].category << ", ";
		cout << itemArray[i].price << endl;
	}
	cout << numArrayItems << endl;													// print number of unsold items
	return 0;
}

bool match(item currentItem, item arrayItem){
	if (currentItem.type == arrayItem.type){
		if ((currentItem.category == " wanted" && arrayItem.category == " for sale") || 
			(currentItem.category == " for sale" && arrayItem.category == " wanted")){
			return true;
		}
		else{
			return false;
		}
	}
	else {
		return false;
	}

}

string comparePrice(item currentItem, item arrayItem) {
	if (currentItem.category == " wanted" && arrayItem.category == " for sale")
		return arrayItem.price;
	else
		return currentItem.price;
}
