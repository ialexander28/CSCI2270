#include <iostream>
#include <string>
#include "MovieTree.hpp"
using namespace std;

// public methods

MovieTree::MovieTree(){
	root = NULL;
}

MovieTree::~MovieTree(){
	DeleteAll(root);
}

void MovieTree::printMovieInventory(){
	printMovieInventory(root);
}

int MovieTree::countMovieNodes(){
	int count = 0;
	countMovieNodes(root, &count);
	return count;
}

void MovieTree::deleteMovieNode(std::string title){
	MovieNodeBST * deletedNode = searchBST(root, title);
	MovieNodeLL * deleteLLNode = searchLL(deletedNode->head,title);
	if (deleteLLNode != nullptr){
		if (deleteLLNode == deletedNode->head){
			if (deletedNode->head->next != nullptr){
				deletedNode->head = deleteLLNode->next;
				delete deleteLLNode;
				return;
			}
			else { // only node in linked list, delete the node in tree
				deletedNode->head = nullptr;
				delete deleteLLNode;
				if (deletedNode != root){
					// no children 
					if (deletedNode->leftChild == nullptr && deletedNode->rightChild == nullptr){
						if (deletedNode->parent->leftChild == deletedNode){
							deletedNode->parent->leftChild = nullptr;
							delete deletedNode;
							return;
						}
						else {
							deletedNode->parent->rightChild = nullptr;
							delete deletedNode;
							return;
						}
					}
					// two children
					else if (deletedNode->leftChild != nullptr && deletedNode->rightChild != nullptr){
						MovieNodeBST * minNode = treeMinimum(deletedNode->rightChild);
						if (minNode->parent == deletedNode){
							if (deletedNode->parent->leftChild == deletedNode){
								deletedNode->parent->leftChild = minNode;
							}
							if (deletedNode->parent->rightChild == deletedNode){
								deletedNode->parent->rightChild = minNode;
							}
							minNode->parent = deletedNode->parent;
							minNode->leftChild = deletedNode->leftChild;
							minNode->leftChild->parent = minNode;
							delete deletedNode;
							return;
						}
						else{
							if (deletedNode->parent->leftChild == deletedNode){
								deletedNode->parent->leftChild = minNode;
							}
							if (deletedNode->parent->rightChild == deletedNode){
								deletedNode->parent->rightChild = minNode;
							}
							minNode->parent = deletedNode->parent;
							minNode->leftChild = deletedNode->leftChild;
							deletedNode->leftChild->parent = minNode;
							minNode->rightChild = deletedNode->rightChild;
							deletedNode->rightChild->parent = minNode;
							delete deletedNode;
							return;
						}
					}
					// only left child
					else if (deletedNode->leftChild != nullptr && deletedNode->rightChild == nullptr){
						MovieNodeBST * temp = deletedNode->leftChild;
						deletedNode->parent->leftChild = temp;
						temp->parent = deletedNode->parent;
						delete deletedNode;
						return;
					}
					// only right child
					else{
						MovieNodeBST * temp = deletedNode->rightChild;
						deletedNode->parent->rightChild = temp;
						temp->parent = deletedNode->parent;
						delete deletedNode;
						return;
					}
				}
				else{ // issa root
					// no children 
					if (deletedNode->leftChild == nullptr && deletedNode->rightChild == nullptr){
						root = nullptr;
						delete deletedNode;
					}
					// two children
					else if (deletedNode->leftChild != nullptr && deletedNode->rightChild != nullptr){
						MovieNodeBST * minNode = treeMinimum(deletedNode->rightChild);
						if (minNode->parent == deletedNode){
							minNode->leftChild = deletedNode->leftChild;
							minNode->parent->leftChild = nullptr;
							minNode->parent = nullptr;
							minNode->leftChild->parent = minNode;
							root = minNode;
							delete deletedNode;
							return;
						}
						else{
							minNode->leftChild = deletedNode->leftChild;
							minNode->rightChild = deletedNode->rightChild;
							minNode->parent->leftChild = nullptr;
							minNode->parent = nullptr;
							deletedNode->rightChild->parent = minNode;
							root = minNode;
							delete deletedNode;
							return;
						}
					}
					// only left child
					else if (deletedNode->leftChild != nullptr && deletedNode->rightChild == nullptr){
						root = deletedNode->leftChild;
						deletedNode->leftChild->parent = nullptr;
						delete deletedNode;
						return;
					}
					// only right child
					else{
						root = deletedNode->rightChild;
						deletedNode->rightChild->parent = nullptr;
						delete deletedNode;
						return;
					}
				}
			}
		}
		else {
			MovieNodeLL * current = deletedNode->head;
			while (current->next != nullptr){
				if (current->next == deleteLLNode){
					current->next = deleteLLNode->next;
					delete deleteLLNode;
					return;
				}
				else{
					current = current->next;
				}
			}
		}
	}
	else{
		cout << "Movie not found." << endl;
	}
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
	char firstLetter = title.at(0);
	MovieNodeBST * newNode = new MovieNodeBST(firstLetter);
	MovieNodeLL * newLLNode = new MovieNodeLL(ranking, title, releaseYear, quantity);
	if (root == nullptr){
		root = newNode;
		root->head = new MovieNodeLL(ranking, title, releaseYear, quantity);
	}
	else {
		MovieNodeBST * current = root;
		while (current != nullptr){
			if (firstLetter < current->letter){
				if (current->leftChild == nullptr){
					current->leftChild = newNode;
					current->leftChild->parent = current;
					current->leftChild->head = newLLNode;
					return;
				}
				else {
					current = current->leftChild;
				}
			}
			if (firstLetter > current->letter){
				if (current->rightChild == nullptr){
					current->rightChild = newNode;
					current->rightChild->parent = current;
					current->rightChild->head = newLLNode;
					return;
				}
				else {
					current = current->rightChild;
				}
			}
			if (current->letter == firstLetter){
				MovieNodeLL * currentLL = current->head;
				MovieNodeLL * prev = nullptr;
				while (currentLL != nullptr){
					if (title.compare(currentLL->title) < 0){
					    if (currentLL == current->head){
					    	newLLNode->next = current->head;
					        current->head = newLLNode;
					        return;
					    }
					    else {
						    prev->next = newLLNode;
						    prev->next->next = currentLL;
					    	return;
						}
					}
					else if(title.compare(currentLL->title) > 0){
						if (currentLL->next == nullptr) {
							currentLL->next = newLLNode;
							return;
						}
						else {
							prev = currentLL;
							currentLL = currentLL->next;
						}
					}
					else {
						currentLL->quantity += quantity;
						return;
					}
				}
			} 
		}
	}
}

void MovieTree::findMovie(std::string title){
	MovieNodeBST * movie = searchBST(root, title);
	if (movie != nullptr){
		MovieNodeLL * foundMovie = searchLL(movie->head, title);
		cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
	}
	else {
		cout << "Movie not found." << endl;
	}
}

void MovieTree::rentMovie(std::string title){
	MovieNodeBST * movie = searchBST(root, title);
	if (movie != nullptr){
		MovieNodeLL * foundMovie = searchLL(movie->head, title);
		foundMovie->quantity--;
		cout << "Movie has been rented." << endl;
		cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
        if (foundMovie->quantity == 0){
        	deleteMovieNode(title);
        }
	}
	else {
		cout << "Movie not found." << endl;
	}
}

// private methods

//use this for the post-order traversal deletion of the tree
void MovieTree::DeleteAll(MovieNodeBST * node){
	if (node->leftChild != nullptr){
		DeleteAll(node->leftChild);
	}
	if (node->rightChild != nullptr){
		DeleteAll(node->rightChild);
	}
	MovieNodeLL * current = node->head;
	while (current != nullptr){
		cout << "Deleting: " << current->title << endl;
		deleteMovieNode(current->title);
		current = current->next;
	}
}

void MovieTree::printMovieInventory(MovieNodeBST * node){
	if (node != nullptr){
		if (node->leftChild != nullptr){
			printMovieInventory(node->leftChild);
		}
		MovieNodeLL * current = node->head;
		while (current != nullptr){
			cout << "Movie: " << current->title << " " << current->quantity << endl;
			current = current->next;
		}
		if (node->rightChild != nullptr){
			printMovieInventory(node->rightChild);
		}
	}
}

void MovieTree::countMovieNodes(MovieNodeBST * node, int * c){
	if (node != nullptr) {
	    MovieNodeLL * current = node->head;
		while (current != nullptr){
		    *c = *c + 1;
		    current = current->next;
		}
		countMovieNodes(node->leftChild, c);
		countMovieNodes(node->rightChild, c);
	}
}

//use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
MovieNodeBST * MovieTree::searchBST(MovieNodeBST * node, std::string title){
	if (node != nullptr){
		if (title.at(0) < node->letter && node->leftChild != nullptr){
			return searchBST(node->leftChild, title);
		}
		else if (title.at(0) > node->letter && node->rightChild != nullptr){
			return searchBST(node->rightChild, title);
		}
		else if (title.at(0) == node->letter){
			if (searchLL(node->head, title) != nullptr){
				return node;
			}
			else{
				return nullptr;
			}
		}
		else{
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}

//use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
MovieNodeLL * MovieTree::searchLL(MovieNodeLL * head, std::string title){
	MovieNodeLL * current = head;
	while (current != nullptr){
		if (current->title == title){
			return current;
		}
		else{
			current = current->next;
		}
	}
	return nullptr;
}

//use this to find the left most leaf node of the BST, you'll need this in the delete function
MovieNodeBST * MovieTree::treeMinimum(MovieNodeBST *node){
	if (node != nullptr){
		while (node->leftChild != nullptr){
			node = node->leftChild;
		}
		return node;
	}
	else {
		return nullptr;
	}
}