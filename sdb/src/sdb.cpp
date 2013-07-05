//============================================================================
// Name        : sdb.cpp
// Author      : Andrew Golubev
// Version     :
// Copyright   : GPLv3
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdx.h"
#include "Table.h"

int main() {
	Table::init_base_structure();
	queue<string> fi = split("dog.father.owner.name",'.');

	while(fi.size() > 1){
		cout << "join:" << fi.front() << endl;
		fi.pop();
	}
	cout << "field:" << fi.front() << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

