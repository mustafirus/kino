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
	typedef deque<RKey> RKeys;
	typedef RFieldVectorOwner RFields;

	Query*		pQuery;
	RFields		rfields;

	RKeys		rkeys;
	Recordset(Query* pq) : pQuery(pq) {

	}

	virtual ~Recordset() {

	}
	void Load();
	void Save();
};

#endif /* RECORDSET_H_ */
