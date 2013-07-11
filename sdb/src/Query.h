// Query.h: interface for the Query class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QUERY_H_
#define QUERY_H_

#include "Table.h"

STD_TYPEDEFS2(QField,Field*)
//STD_TYPEDEFS(QTable)
class QTable;
STD_TYPEDEFS2(Query,Table*)

class RKey;

class QField {
	QTable* pQTable;
public:
	Field* pField;
	QField(QTable* pqt, Field* pf) :
			pQTable(pqt), pField(pf) {
	}
	virtual ~QField() {
	}
	string name(){
		return pField->name;
	}
	string alias();		// { return pQTable->alias; }
};

class QTable {
public:
	typedef QFieldMapOwner QFields;
	typedef stringstream SqlStmt;
	Table* pNTable;
	string alias;
	QTable* parent;
	QFields qfields;
	FKey* pFKey;
	QTable* next;

public:
// Construction/Destruction
	QTable(Table* pt) :
			pNTable(pt), alias("master"), parent(NULL), pFKey(NULL), next(NULL) {
	}

	QTable(QTable* pqt, FKey* pfk) :
			pNTable(pfk->pPKey->pTable), alias(genAlias()), parent(pqt), pFKey(
					pfk), next(NULL) {
	}
	virtual ~QTable() {
		delete next;
	}

// Construction helpers
	QTable* join(string fkeyname) {
		FKey* pfk = pNTable->getFKey(fkeyname);
		if (!pfk)
			return NULL;
		return join(pfk);
	}

	QTable* join(FKey* pfk) {
		QTable* pqt = find(this, pfk);
		if (pqt)
			return pqt;
		pqt = add(new QTable(this, pfk));
		return pqt;
	}
	QTable* getLink(QTable* pqt);
//	QTable* GetLink(QTable* pqtlink, QTable* pqtthis = NULL);
	QField* getQField(string name) {
		Field* pf;
		pf = pNTable->getField(name);
		if (!pf)
			return NULL;
		return getQField(pf);
	}
	QField* getQField(Field* pf) {
		auto it = qfields.find(pf);
		return it != qfields.end() ? it->second.get() : addQField(pf);
	}
	QFieldVector getQFields(FieldVector& fv) {
		QFieldVector qfv;
		for (auto f : fv) {
			qfv.push_back(getQField(f));
		}
		return qfv;
	}

// RKey creation

	QFieldVector getKeyFields() {
		if (parent)
			return parent->getQFields(pFKey->fields);
		else
			return getQFields(pNTable->pkey.fields);
	}

	bool isMaster() {
		return parent == NULL;
	}

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
	QField* addQField(Field* pf) {
		QField* pqf = new QField(this, pf);
		qfields.emplace(pf, QFieldPtr(pqf));
		return pqf;
	}
	static string genAlias() {
		static int anum = 0;
		return string("t") + to_string(++anum);
	}
};

class Query {
	typedef QueryMapOwner Queries;
public:
	QTable* pQTable;

	Query(Table* pt) {
		pQTable = new QTable(pt);
	}

	virtual ~Query() {
		delete pQTable;
	}

// Creation helpers
	QField* getQField(string str) {
		queue < string > parts = split(str, '.');
		QTable* last = pQTable;

		while (parts.size() > 1) {
			last = last->join(parts.front());
			parts.pop();
		}
		return last->getQField(parts.front());
	}
	static Queries queries;
	static Query* getQuery(Table* pt) {
		QueryPtr& pq = queries[pt];
		if (!pq)
			pq.reset(new Query(pt));
		return pq.get();
	}
};

#endif // QUERY_H_
