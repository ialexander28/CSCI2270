#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct node{
	int key;
	node *next;
	node(int k, node *n){
		key = k;
		next = n;
	}
};

void addNode(node * prev){
	if (prev == NULL){
		return;
	}
	node * newNode = new node(3,NULL);
	newNode->next = prev->next;
	prev->next = newNode;
}

void printNode(node * p){
	while (p != NULL){
		cout << p->key << endl;
		p = p->next;
	}
}

int main(){
	int i = 1;
	node *head = new node(i, NULL);
	node *p = head;
	i++;
	while (i < 10){
		node *n = new node(i, NULL);
		p->next = n;
		p = n;
		i++;
	}
	p = head;
	printNode(p);
	while (p != NULL){
		if ((p->key)%2 == 0){
			addNode(p);
		}
		p = p->next;
	}
	p = head;
	cout << "#" << endl;
	printNode(p);
	delete[] p;
	return 0;
}