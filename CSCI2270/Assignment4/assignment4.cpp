#include <iostream>
#include <string>
#include "CommunicationNetwork.h"
using namespace std;

void printMenu(){
	cout << "======Main Menu======" << endl;
	cout << "1. Build Network" << endl;
	cout << "2. Print Network Path" << endl;
	cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
	cout << "4. Add City" << endl;
	cout << "5. Delete City" << endl;
	cout << "6. Clear Network" << endl;
	cout << "7. Quit" << endl;
}

int main(int argc, char * argv[]){
	string userInput;
	string cityNew, cityPrevious, cityDelete;
	CommunicationNetwork CityNetwork;
	while (userInput != "7") {
		printMenu();
		getline(cin, userInput);
		if (userInput == "1"){
			CityNetwork.buildNetwork();
			CityNetwork.printNetwork();
		}
		else if (userInput == "2"){
			CityNetwork.printNetwork();
		}
		else if (userInput == "3"){
			CityNetwork.transmitMsg(argv[1]);
		}
		else if (userInput == "4"){
			cout << "Enter a city name:" << endl;
			getline(cin, cityNew);
			cout << "Enter a previous city name: " << endl;
			getline(cin, cityPrevious);
			CityNetwork.addCity(cityNew, cityPrevious);
		}
		else if (userInput == "5"){
			cout << "Enter a city name:" << endl;
			getline(cin, cityDelete);
			CityNetwork.deleteCity(cityDelete);
		}
		else if (userInput == "6"){
			CityNetwork.deleteNetwork();
		}
		else if (userInput == "7"){
			cout << "Goodbye!" << endl;
		}
		else {
			cout << "Invalid Input!" << endl;
		}
	}
	return 0;
}