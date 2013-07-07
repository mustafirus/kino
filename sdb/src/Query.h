// Query.h: interface for the Query class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QUERY_H_
#define QUERY_H_

#include "Table.h"

STD_TYPEDEFS2(QField,Field*)
STD_TYPEDEFS(QTable)
STD_TYPEDEFS(Query)

class RKey;

class QField
{
	QTable* pQTable;
public:
	Field*	pField;
	QField(QTable* pqt, Field* pf) :
		pQTable(pqt),
		pField(pf){
	}
	virtual ~QField(){};
};


class QTable
{
public:
	typedef QFieldMapOwner	QFields;
	typedef stringstream	SqlStmt;
	Table*  pNTable;
	string	alias;
	QTable* parent;
	QFields qfields;
	FKey*	pFKey;
	QTable* next;

public:
// Construction/Destruction
	QTable(Table* pt) :
		pNTable(pt),
		alias("master"),
		parent(NULL),
		pFKey(NULL),
		next(NULL){
	}

	QTable(QTable* pqt, FKey* pfk) :
			pNTable(pfk->pPKey->pTable),
			alias(getAlias()),
			parent(pqt),
			pFKey(pfk),
			next(NULL){
	}
	virtual ~QTable(){
		delete next;
	}

// Construction helpers
	QTable* join(string fkeyname)	{
		FKey* pfk = pNTable->getFKey(fkeyname);
		if(!pfk)
			return NULL;
		return join(pfk);
	}

	QTable* join(FKey* pfk) {
		QTable* pqt = find(this, pfk);
		if(pqt)
			return pqt;
		pqt = add(new QTable(this, pfk));
		return pqt;
	}
	QTable* getLink(QTable* pqt);
//	QTable* GetLink(QTable* pqtlink, QTable* pqtthis = NULL);
	QField* getQField(string name) {
		Field* pf;
		pf = pNTable->getField(name);
		if(!pf)
			return NULL;
		QField* pqf = getQField(pf);
		return pqf ? pqf : addQField(pf);
	}

	bool	isMaster(){return parent == NULL;};

// RKey creation

	void GetKeyFields(QFields& qtrg);
	QTable* getFirstChild()
	{
		if(!parent)
			return this;
		if(!parent->parent)
			return this;
		else
			return parent->getFirstChild();
	};
	void		sql_select(SqlStmt& str, bool first = true);
	void		sql_delete(SqlStmt& str);
	string& 	aliaS(){return alias;};
	void		set_mark(bool this_only);
	const char* GetRest();
private:
	QTable* add(QTable* pqt) {
		if (next)
			return next->add(pqt);
		else {
			next = pqt;
			pqt->next = NULL;
			return pqt;
		}
	}
	QTable* find(QTable* pqt, FKey* pfk) {
		if (parent == pqt && pFKey == pfk)
			return this;
		if (next)
			return next->find(pqt, pfk);
		else
			return NULL;
	}
	QField* addQField(Field* pf){
		QField* pqf = new QField(this, pf);
		qfields.emplace(pf,QFieldPtr(pqf));
		return pqf;
	}
	QField* getQField(Field* pf){
		return qfields[pf].get();
	}
	static string getAlias(){
		static int anum=0;
/*
		char s[64];
		sprintf(s, "t%d", anum);
		return s;
*/
		return string("t") + to_string(++anum);
	}
};

class Query  
{
	QTable* pQTable;
public:

	Query(Table* pt){
		pQTable = new QTable(pt);
	}

	virtual ~Query() {
		delete pQTable;
	}


// Creation helpers
	QField* getQField(string str){
		queue<string> parts = split(str,'.');
		QTable* last = pQTable;


		while(parts.size() > 1){
			last=last->join(parts.front());
			parts.pop();
		}
		return last->getQField(parts.front());
	}
};

#endif // QUERY_H_

