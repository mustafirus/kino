//============================================================================
// Name        : sdb.cpp
// Author      : Andrew Golubev
// Version     :
// Copyright   : GPLv3
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdx.h"
#include "Table.h"
#include "Query.h"

int main() {
	Table::init_base_structure();
	Table* pt = Table::tables["sdb_tables"].get();
	Query* pq = new Query(pt);
	pq->getQField("id");
	pq->getQField("name");
	delete pq;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

