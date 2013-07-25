/*
 * Recordset.h
 *
 *  Created on: 13 июля 2013
 *      Author: golubev
 */

#ifndef RECORDSET_H_
#define RECORDSET_H_

#include "Record.h"
class PRKey{
	typedef RFieldVectorOwner RFields;

	RFields rfields;
};

class Recordset {
public:
	typedef deque<vector<RField> > RKeysFields;
	typedef vector<RField> RFields;

	Query*		pQuery;
	RKeysFields rkeysfields;
	RFields		rfields;

	Recordset(Query* pq) : pQuery(pq) {

	}

	virtual ~Recordset() {

	}
	void Load();
	void Save();
};

#endif /* RECORDSET_H_ */
