#include <iostream>
#include "doublyLL.cpp"

int main(){
	doublyLL LL;
	for (int i=0; i < 20; i++){
		if (i == 4 || i == 7 || i == 9 || i == 13 || i == 18){
			LL.insertNodeAtEnd(4);
		}
		else {
			LL.insertNodeAtEnd(i);
		}
	}
	LL.print_list();
	LL.deleteNode(4);
	LL.deleteNode(4);
	LL.deleteNode(4);
	LL.deleteNode(4);
	LL.deleteNode(4);
	LL.print_list();
	return 0;
}