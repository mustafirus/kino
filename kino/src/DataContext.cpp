// DataContext.cpp: implementation of the DataContext class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "dblib.h"
#include "ErrorCodes.h"
#include "Exception.h"
#include "Kinores.h"
#include "DataContext.h"

#define GetApp() Application::GetApp()
#define MAXACCELS	10
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DataContext::~DataContext(){
	ASSERT(_isFree());
};

void DataContext::Create(const char* table)
{
	ASSERT(_isFree());

	pQuery = RecordSet::pDict->GetQuery(table);
	ASSERT(pQuery);

	szForm = RecordSet::pDict->GetForm(pQuery, 2);
	if(!szForm)
	{
		Exception::ex.printf("form not fount %s %s", 'e', ((Table*)*(QTable*)*pQuery)->name,
			((Table*)*(QTable*)*pQuery)->mPKey.name);
		throw &Exception::ex;
	}

//	((char*)szFrameName) = (char*)((QTable*)*pQuery)->GetName(1);
}

void DataContext::Create(RKey* prk, RLink* prl, uint nID)
{
	ASSERT(_isFree());
	pRKey = prk;
	pRLink = prl;
	szForm = RecordSet::pDict->GetForm(prk, nID);
//	((char*)szFrameName) = (char*)((QTable*)*prk)->GetName(nID-1);
}

void DataContext::FreeContext()
{
	pQuery = NULL;
	if(pRLink)
	{
		ASSERT(pRec);
		delete pRLink;
		pRLink = NULL;
	}
	pRec = NULL;
	pRKey = NULL;
	rt = none;
	ifdel(szForm);
	szFrameName = NULL;
	szForm = NULL;
	pWnd = NULL;
	bAutoSave = false;
}

Record*	DataContext::GetRecord(bool create /*= true*/)
{
	if(!create)
		if(rt == rec)
			return pRec;
		else
			return NULL;
	ASSERT(rt != rset && pRKey);
	rt = rec;
	if(!pRec)
	{
		pRec = new Record(pRKey);
		if(pRLink)
		{
			pRec->SetLink(pRLink, pRKey);
			pRLink = NULL;
		}
	}
	return pRec;
}

RecordSet* DataContext::GetRecordSet()
{
	ASSERT(rt != rec);
	rt = rset;
	if(pRec)
		return (RecordSet*)pRec;
	if(pQuery)
		pRec = new RecordSet(20, pQuery);
	else
		pRec = new RecordSet(20, *pRKey);
	if(pRLink)
	{
		pRec->SetLink(pRLink, NULL);
		pRLink = NULL;
	}
	return (RecordSet*)pRec;
}

