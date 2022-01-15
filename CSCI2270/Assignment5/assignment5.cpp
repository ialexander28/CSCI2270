#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

void printMenu(){
	cout << "======Main Menu=====" << endl;
	cout << "1. Enqueue word" << endl;
	cout << "2. Dequeue word" << endl;
	cout << "3. Print queue" << endl;
	cout << "4. Enqueue sentence" << endl;
	cout << "5. Quit" << endl;
}

int main(){
	string userInput;
	string word, sentence;
	Queue wordBuffer(10);
	while (userInput != "5"){
		printMenu();
		getline(cin, userInput);
		if (userInput == "1"){
			cout << "word: ";
			getline(cin, word);
			wordBuffer.enqueue(word);
		}
		else if (userInput == "2"){
			wordBuffer.dequeue();
		}
		else if (userInput == "3"){
			wordBuffer.printQueue();
		}
		else if (userInput == "4"){
			cout << "sentence: ";
			getline(cin, sentence);
			wordBuffer.enqueueSentence(sentence);
		}
		else if (userInput == "5"){
			cout << "Goodbye!" << endl;
		}
		else {
			cout << "Invalid input!" << endl;
		}
	}
	return 0;
}