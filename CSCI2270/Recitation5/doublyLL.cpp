#include <iostream>
#include "doublyLL.h"
using namespace std;

doublyLL::doublyLL() {

}

doublyLL::doublyLL(int nodeID) {
	//create head node
	head = createNode(nodeID, nullptr, nullptr);
	tail = head;
}

doublyLL::~doublyLL() {

}


Node* doublyLL::createNode(int nodeID, Node* nodePrev, Node* nodeNext) {
	Node* newNode = new Node;
	newNode->id = nodeID;
	newNode->next = nodeNext;
	newNode->prev = nodePrev;

	return newNode;
}

bool doublyLL::insertNodeAtEnd(int nodeID) {
	if (head == nullptr) {
		//nothing in the list
		head = createNode(nodeID, nullptr, nullptr);
		tail = head;
	}
	else {
		Node* newNode = createNode(nodeID, tail, nullptr);
		tail->next = newNode;
		tail = newNode;
	}
	return true;
}

bool doublyLL::deleteNode(int nodeID){
	Node * current = head;
	while (current != nullptr){
		if (current->id == nodeID){
			current->prev->next = current->next;
			current->next->prev = current->prev;
			delete current;
			break;
		}
		else {
			current = current->next;
		}
	}
	return true;
}

void doublyLL::print_list(){
	if (head == nullptr){
		return;
	}
	Node * current = head;
	while (current != nullptr){
		if (current->next == nullptr){
			cout << endl;
			break;
		}
		else {
			cout << current->id << " ";
			current = current->next;
		}
	}
}








