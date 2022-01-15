#include <iostream>
#include "BST.cpp"

using namespace std;

int main(){
	BST tree(4);
	for (int i=0; i<10; i++){
		tree.insertNode(i);
	}
	tree.printTree();
	if (tree.searchKey(8)){
		cout << "found!" << endl;
	}
}