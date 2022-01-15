#include <iostream>
#include <sstream>
#include <string>
#include "Queue.h"
using namespace std;

Queue::Queue(int qs){
	queueSize = qs;
	arrayQueue = new std::string[queueSize];
	queueHead = 0;
	queueTail = 0;
	queueCount = 0;
}

Queue::~Queue(){
	delete[] arrayQueue;
	arrayQueue = nullptr;
}

void Queue::enqueue(std::string word){
	if (!queueIsFull()){
		arrayQueue[queueTail] = word;
		if (queueTail == queueSize - 1){
			queueTail = 0;
		}
		else {
			queueTail++;
		}
		queueCount++;
		cout << "E: " << word << endl;
		cout << "H: " << queueHead << endl;
		cout << "T: " << queueTail << endl;
	}
	else {
		cout << "Queue full" << endl;
	}
}

void Queue::dequeue(){
	if (!queueIsEmpty()){
		std::string word = arrayQueue[queueHead];
		queueCount--;
		if (queueHead == queueSize - 1){
			queueHead = 0;
		}
		else {
			queueHead++;
		}
		cout << "H: " << queueHead << endl;
		cout << "T: " << queueTail << endl;
		cout << "word: " << word << endl;
	}
	else {
		cout << "Queue is empty" << endl;
	}
}

void Queue::printQueue(){
	int current = queueHead;
	if (!queueIsEmpty()){
		for (int i=0; i < queueCount; i++){
			cout << current << ": " << arrayQueue[current] << endl;
			if (current == queueSize - 1){
				current = 0;
			}
			else {
				current++;
			}
		}
	}
	else {
		cout << "Empty" << endl;
	}
}

void Queue::enqueueSentence(string sentence){
	stringstream ss(sentence);
	string currentWord;
	while (ss >> currentWord){
		if (!queueIsFull()){
			enqueue(currentWord);
		}
		else {
			cout << "Queue is full" << endl;
		}
	}
}


bool Queue::queueIsFull(){
	if (queueCount == queueSize) {
		return true;
	}
	else {
		return false;
	}
}

bool Queue::queueIsEmpty(){
	if (queueCount == 0){
		return true;
	}
	else {
		return false;
	}
}