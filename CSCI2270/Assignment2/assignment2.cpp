#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct wordItem {
	string word;
	int count = 0;
};

void getStopWords(char *ignoreWordFileName, string ignoreWords[]){
	ifstream ignoreFile;
	ignoreFile.open(ignoreWordFileName);
	string data;
	if (ignoreFile.is_open()){
		for(int i=0; i < 50; i++){
			getline(ignoreFile, data);
			ignoreWords[i] = data;
		}
	}
	ignoreFile.close();
}

bool isStopWord(string word, string ignoreWords[]){
	for (int i=0; i < 50; i++){
		if (word.compare(ignoreWords[i]) == 0){
			return true;
		}
	}
	return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length){
	int total = 0;
	for (int i=0; i < length; i++){
		total = total + list[i].count;
	}
	return total;
}

void arraySort(wordItem list[], int length){
	for (int i=0; i < length; i++){
		for (int j=i+1; j < length; j++){
			if (list[i].count < list[j].count){
				wordItem temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

void printTopN(wordItem wordItemList[], int topN){
	for (int i=0; i < topN; i++){
		cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
	}
}

void resize(wordItem *& oldArray, int * capacity){ // Note: why do we have to use *&
	int newCapacity = *capacity * 2;
	wordItem * newArray = new wordItem[newCapacity];
	for (int i=0; i < *capacity; i++){
		newArray[i] = oldArray[i];
	}
	delete[] oldArray;
	oldArray = newArray;
	*capacity = newCapacity;
}

int main(int argc, char *argv[]){
	if (argc != 4){
		cout << "Not Enough Arguments!" << endl;
		return -1;
	}
	ifstream hungergamesFile;
	hungergamesFile.open(argv[2]);
	int topN = stoi(argv[1]);
	int totalNonStopWords = 0;
	int numberDoubled = 0;
	string ignoreWords[50];
	getStopWords(argv[3], ignoreWords);
	string data;
	int capacity = 100;
	int numElements = 0;
	int matchStatus = 0;
	wordItem * list = new wordItem[capacity]; // list of non stop words
	if (hungergamesFile.is_open()){
		while (getline(hungergamesFile, data)){
			stringstream ss(data);
			string currentWord;
			while (ss >> currentWord){ // extract word from stream, with whitespace as delimiter
				if (isStopWord(currentWord, ignoreWords) == false){	// non stop word
					for (int i=0; i < numElements; i++){
						if (currentWord.compare(list[i].word) == 0){ // found existing non stop word
							list[i].count++;
							matchStatus = 1;
							break;
						}
					}
					if (matchStatus == 0){		// new non stop word
						list[numElements].word = currentWord;
						list[numElements].count = 1;
						numElements++;
						if (numElements == capacity){
							resize(list, &capacity);
							numberDoubled++;
						}
					}
				}
				matchStatus = 0;
			}
		}
		hungergamesFile.close();
	}
	else {
		cout << "File opened unsuccessfully!" << endl;
		return -1;
	}
	arraySort(list, numElements);
	printTopN(list, topN);
	totalNonStopWords = getTotalNumberNonStopWords(list, numElements);
	cout << "#" << endl;
	cout << "Array doubled: " << numberDoubled << endl;
	cout << "#" << endl;
	cout << "Unique non-common words: " << numElements << endl;
	cout << "#" << endl;
	cout << "Total non-common words: " << totalNonStopWords << endl;
	delete[] list;
	return 0;
}