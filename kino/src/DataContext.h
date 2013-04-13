// DataContext.h: interface for the DataContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATACONTEXT_H__76248D13_4B4F_11D2_A732_204C4F4F5020__INCLUDED_)
#define AFX_DATACONTEXT_H__76248D13_4B4F_11D2_A732_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Record;
class RecordSet;
class RKey;
class Query;
class QTable;
class FrameWnd;
class RLink;

class DataContext
{
	Query*		pQuery;
	Record*		pRec;
	RKey*		pRKey;
	RLink*		pRLink;
	enum{none, rec, rset} rt;

public:
	char*		szFrameName;
	char*		szForm;
	FrameWnd*	pWnd;
	bool		bAutoSave; 

public:
	DataContext() : pQuery(NULL), pRec(NULL), pRKey(NULL), pRLink(NULL), rt(none),
		szFrameName(NULL), szForm(NULL), pWnd(NULL), bAutoSave(false){};
	~DataContext();
	void Create(const char* table);
	void Create(RKey* prk, RLink* prl, uint nID);
	void FreeContext();

	RecordSet*	GetRecordSet();
	Record*		GetRecord(bool create = true);
	Record*		GetDefRecord(){return pRec;};
	RKey*		GetRKey(){return pRKey;};

private:
	bool _isFree()
	{
#ifdef _DEBUG
		return pQuery == NULL && pRec == NULL && pRKey == NULL &&
		pRLink == NULL && rt == none &&	szFrameName == NULL && szForm == NULL;
#else
		return true;
#endif //_DEBUG
	};
};

#endif // !defined(AFX_DATACONTEXT_H__76248D13_4B4F_11D2_A732_204C4F4F5020__INCLUDED_)
