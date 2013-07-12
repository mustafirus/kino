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

	RFieldVector loadrfs;
	QFieldList   loadqfs;
	for (auto const& rf : rfields) {
		if (rf->isModified())
			continue;
		if (refresh or rf->isDirty()) {
			loadrfs.push_back(rf.get());
			loadqfs.push_back(rf->pQField);
		}
	}
	if(!loadrfs.size())
		return;

	string sql = pQuery->getSelect(loadqfs, pPRKey->qFields);



	Database::Stmt* ps = Database::pdb->prepare(sql);
	try{
/*
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
*/
	}catch(...)
	{
		ps->release();
		return;
	}
/*
	for(int i = 0; i<pRFields.size(); i++)
	{
		if(pRFields[i]->state != RField::s_modified)
			pDB->CheckData(pRFields[i]);
	}
*/
	state /= s_dirty;
}
