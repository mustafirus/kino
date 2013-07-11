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
	Table* pt = Table::tables["sdb_fields"].get();
	Query* pq = new Query(pt);
	list<QField*> qfs;
	qfs.push_back(pq->getQField("id"));
	qfs.push_back(pq->getQField("name"));
	qfs.push_back(pq->getQField("table.name"));
	QFieldVector wfs;
	wfs.push_back(pq->getQField("id"));
	string sql = pq->getSelect(qfs,wfs);
	delete pq;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << sql << endl; // prints sql

	return 0;
}

