/*
 * Record.cpp
 *
 *  Created on: 6 июля 2013
 *      Author: golubev
 */

#include "stdx.h"
#include "Record.h"

RKey::RKey(QTable* pqt, Record* pRecSrc) :
		pQTable(pqt) {
	QFields qf = pqt->getKeyFields();
	for (auto it : qf) {
		pRecSrc->getRField(it);
		pRFields.push_back(pRecSrc->getRField(it));
	}
	pQuery = Query::getQuery(pqt->pNTable);
	pqt = pQuery->pQTable;
	pQFields = pqt->getKeyFields();
}
