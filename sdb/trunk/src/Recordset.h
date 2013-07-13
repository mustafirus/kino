/*
 * Recordset.h
 *
 *  Created on: 13 июля 2013
 *      Author: golubev
 */

#ifndef RECORDSET_H_
#define RECORDSET_H_

#include "Record.h"

class Recordset: public Record {
public:
	typedef deque<RKey> RKeys;

	RKeys		rkeys;
	Recordset() {
		// TODO Auto-generated constructor stub

	}
	virtual ~Recordset() {
		// TODO Auto-generated destructor stub
	}
};

#endif /* RECORDSET_H_ */
