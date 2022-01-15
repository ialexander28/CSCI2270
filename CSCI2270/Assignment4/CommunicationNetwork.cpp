#include <iostream>
#include "CommunicationNetwork.h"
using namespace std;

CommunicationNetwork::CommunicationNetwork(){

}

CommunicationNetwork::~CommunicationNetwork(){
	deleteNetwork();
	head = nullptr;
	tail = nullptr;
}

void CommunicationNetwork::addCity(string newCityName, string previousCityName){
	City * newCity = new City(newCityName, nullptr, nullptr, "");
	City * current = head;
	if (head == nullptr) {
		head = newCity;
		tail = newCity;
		return;
	}
	if (previousCityName == "First"){	// adding to the head of network
		newCity->next = current;
		current->previous = newCity;
		head = newCity;
		return;
	}
	if (previousCityName == ""){	// adding to the tail of network
		City * temp = tail;
		temp->next = newCity;
		newCity->previous = temp;
		tail = newCity;
		return;
	}
	while (current != nullptr){
		if (current->cityName == previousCityName){
			newCity->next = current->next;
			current->next = newCity;
			newCity->previous = current;
			return;
		}
		else {
			current = current->next;
		}
	}
}

void CommunicationNetwork::transmitMsg(char * filename){
	if (head == nullptr){
		cout << "Empty list" << endl;
		return;
	}
	ifstream msgFile;
	msgFile.open(filename);
	string word;
	bool tailStatus = false;
	if (msgFile.is_open()){
		City * current = head;
		while (msgFile >> word){
			current = head;
			current->message = word;
			while (current != nullptr){
				if (current->next == nullptr){
					cout << current->cityName;
					cout << " received ";
					cout << current->message << endl;
					tailStatus = true;
				}
				if (current->previous == nullptr && tailStatus == true){
					tailStatus = false;
					break;
				}
				if (tailStatus == false){
					cout << current->cityName;
					cout << " received ";
					cout << current->message << endl;
					current->next->message = current->message;
					current->message = "";
					current = current->next;
				}
				if (tailStatus == true){
					current->previous->message = current->message;
					current->message = "";
					current = current->previous;
					cout << current->cityName;
					cout << " received ";
					cout << current->message << endl;
				}				
			}
		}
	}
	msgFile.close();
}

void CommunicationNetwork::printNetwork(){
	cout << "===CURRENT PATH===" << endl;
	if (head == nullptr){
		cout << "NULL" << endl;
		return;
	}
	City * current = head;
	cout << "NULL <- ";
	while (current != nullptr){
		if (current->next == nullptr){
			cout << current->cityName;
			cout << " -> ";
			cout << "NULL" << endl;
			break;
		}
		else {
			cout << current->cityName;
			cout << " <-> ";
			current = current->next;
		}
	}
	cout << "==================" << endl;
}

void CommunicationNetwork::buildNetwork(){
	string names[] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", 
	"Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
	head = new City(names[0], nullptr, nullptr, "");
	City * p = head;
	for (int i=1; i < 10; i++){
		City * newCity = new City(names[i], nullptr, nullptr,"");
		p->next = newCity;
		newCity->previous = p;
		p = newCity;
	}
	tail = p;
}

void CommunicationNetwork::deleteCity(string removeCity){
	City * current = head;
	bool foundStatus = false;
	while (current != nullptr){
		if (current->cityName == removeCity){
			if (current->previous == nullptr){
				current->next->previous = current->previous;
				head = current->next;
			}
			else if (current->next == nullptr){
				current->previous->next = current->next;
				tail = current->previous;
			}
			else {
				current->previous->next = current->next;
				current->next->previous = current->previous;
			}
			foundStatus = true;
			delete current;
			break;
		}
		else {
			current = current->next;
		}
	}
	if (foundStatus == false) {
		cout << removeCity << " not found" << endl;
	}
}

void CommunicationNetwork::deleteNetwork(){
	City * current = head;
	while (current != nullptr){
		cout << "deleting " << current->cityName << endl;
		deleteCity(current->cityName);
		current = current->next;
	}
}