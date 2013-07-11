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
		rFields.push_back(pRecSrc->getRField(it));
	}
	pQuery = Query::getQuery(pqt->pNTable);
	qFields = pQuery->pQTable->getKeyFields();
}
void RField::setModified(){
	 state = s_modified;
	 pRec->setModified();
}

void RField::setDirty(){
	state = s_dirty;
	pRec->setDirty();
}

void Record::Load(bool refresh){

	if (pPRKey->isNull())
		New();
//		ASSERT(pRFields.size());
	RFieldVector loadrfs;
	for (auto const& rf : rfields) {
		if (rf->isModified())
			continue;
		if (refresh or rf->isDirty()) {
			loadrfs.push_back(rf.get());
		}
	}
	if(!loadrfs.size())
		return;

	ostringstream sql;
	sql << "SELECT ";
	for (auto rf : loadrfs) {
//		if (i > 0)
//			str << ", ";
		sql << rf->pQField->alias() << "." << rf->pQField->name();
		(*pRFields[i])->Mark();
	}

	str << "\nFROM ";
	pQuery->pQTable->Select(str);
	ASSERT(pPRKey);
	str << "\nWHERE ";
	pPRKey->Select(str);
	try{
		if(!pDbStmt)
		{
			pDbStmt = pDB->Prepare(str);
		}else
			pDB->Set(pDbStmt);
		pDB->BindParameter(pPRKey);
		for(int i=0; i < pRFields.size(); i++)
		{
			if(pRFields[i]->state == RField::s_modified)
				continue;
			pDB->Bind(i+1, pRFields[i]);
		}
		pDB->Exec();
		if(!pDB->Read())
			return false;
		pDB->FlushEx();
	}catch(DbException* e)
	{
		e->Effect();
		pDB->FlushEx();
		return false;
	}
	for(int i = 0; i<pRFields.size(); i++)
	{
		if(pRFields[i]->state != RField::s_modified)
			pDB->CheckData(pRFields[i]);
	}
	state /= s_dummy;
	return true;

}
