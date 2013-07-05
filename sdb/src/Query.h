// Query.h: interface for the Query class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QUERY_H_
#define QUERY_H_

#include "Table.h"

class QField;
class Field;
class QTable;
class Table;
class RKey;

class QField
{
	Field*	pField;
	QTable* pQTable;
public:
	QField(QTable* pTable, Field* pField);
	virtual ~QField();
};

class QTable
{
public:/// For Link
	Table*  pNTable;
	string	Alias[16];
	QTable* pPTable;
	QField* pQField;
	FKey*	pFKey;
	QTable* next;
	bool	mark;
	int		style;
	QTable* Add(QTable* pqf);
	QTable* Find(QTable* pqt, FKey* pfk);
public:
// Construction/Destruction
	QTable(Table* pTable);
	QTable(QTable* pPTable, FKey* pKey);
	virtual ~QTable();

// Construction helpers
	QTable* Join(const char* fkeyname);
	QTable* Join(FKey* pfk);
	QTable* getLink(QTable* pqt);
//	QTable* GetLink(QTable* pqtlink, QTable* pqtthis = NULL);
	QField* getQField(const char* name);
	void	getQFields(FieldSet& f, QFields& qf);
	const char* GetExtent(const char* str);
	operator Table*(){return pNTable;};
	operator Table&(){return *pNTable;};
	operator QTable*(){return next;};
	operator FKey*(){return pFKey;};
	bool	isMaster(){return pPTable == NULL;};

// RKey creation

	void GetKeyFields(QFields& qtrg);
	QTable* GetFirstChild()
	{
		if(!pPTable)
			return this;
		if(!pPTable->pPTable)
			return this;
		else
			return pPTable->GetFirstChild();
	};
	void		Select(SqlStmt& str, bool first = true);
	void		Delete(SqlStmt& str);
	const char*	AliaS(){return Alias;};
	void		Mark(bool this_only);
	const char* GetRest();
	const char* GetName(int num, int type = 0);
	void		GetNames(PNAMEINFO pn);
private:

};

class Query  
{
//	QField* pQField;
	QTable* pQTable;
friend class Record;
friend class RecordSet;
public:
	Query(Table* pt);
	virtual ~Query();
// Creation helpers
	char* GetQFields(const char* str, QFields& qf, QTable* pqt = NULL);
	void GetKeyFields(QTable* pqt, QFields& qtrg);

protected:

private:
//	Query*	next;

};

#endif // QUERY_H_

