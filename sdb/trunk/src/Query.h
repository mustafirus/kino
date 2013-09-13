// Query.h: interface for the Query class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QUERY_H_
#define QUERY_H_

#include "Table.h"

class RKey;

class QField {
public:
	QTable* pQTable;
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
//	typedef stringstream SqlStmt;
	typedef unordered_set<QTable*> Marks;
	Table* pNTable;
	string alias;
	QTable* parent;
	QFields qfields;
	FKey* pFKey;
//	QTable* next;

public:
// Construction/Destruction
	QTable(Table* pt) :
			pNTable(pt), alias("master"), parent(NULL), pFKey(NULL) {
	}

	QTable(QTable* pqt, FKey* pfk) :
			pNTable(pfk->pPKey->pTable), alias(genAlias()), parent(pqt), pFKey(
					pfk) {
	}
	~QTable() {
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

	void mark( Marks& m ){
		m.insert(this);
		if(parent)
			parent->mark(m);
	}

private:
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
	typedef QueryMapOwner	Queries;
	typedef list<QTable>	QTables;
public:

//	QTable* pQTable;
	QTables qtables;

	Query(Table* pt) {
//		pQTable = new QTable(pt);
		qtables.emplace_back(pt);
	}

	virtual ~Query() {
//		delete pQTable;
	}

	QTable* getMaster(){return &qtables.front();}

	QField* getQField(string str) {
		queue < string > parts = split(str, '.');
		if(parts.empty())
			return nullptr;
		QTable* last = &qtables.front();
		while (&parts.front() != &parts.back()) {//parts.size() > 1

			last = join(last, parts.front());
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

	/*used by record*/
	string getSelect(QFieldList fields, QFieldVector where){
		ostringstream sql;

		QTable::Marks marks;

		sql << "SELECT ";
		const char* coma = "";

		for (auto pqf : fields) {
			sql << coma;
			coma = ", ";
			sql << pqf->alias() << "." << pqf->name();
			pqf->pQTable->mark(marks);
		}

		sql << "\nFROM ";
		bool first = true;

		for(auto &qt : qtables){
			QTable* pqt = &qt;
			if(!marks.count(pqt))
				continue;

			if(first){
				sql << pqt->pNTable->name << " as " << pqt->alias << " ";
				first = false;
				continue;
			}
			sql << "\nJOIN ";
			sql << pqt->pNTable->name << " as " << pqt->alias << " ";
			for(size_t i = 0; i < pqt->pFKey->fields.size(); i++)
			{
				sql << (i ? " AND " : " ON ") << pqt->alias << "." << pqt->pFKey->pPKey->fields[i]->name <<
					" = " << pqt->parent->alias << "." <<
					pqt->pFKey->fields[i]->name;
			}
		}

		sql << "\nWHERE ";

		for(size_t i = 0, s = where.size(); i < s; i++)
		{
			if(i!=0)
				sql << " AND ";
			QField* pqf = where[i];
			sql << pqf->alias() << "." << pqf->name() << " = ?";

		}

		return sql.str();
	}


private:
	QTable* find(QTable* pqt, FKey* pfk) {
		for(auto & qt : qtables){
			if (qt.parent == pqt && qt.pFKey == pfk)
				return &qt;
		}
		return NULL;
	}

	QTable* join(QTable* pqt_parent, string fkeyname) {
		FKey* pfk = pqt_parent->pNTable->getFKey(fkeyname);
		if (!pfk)
			return nullptr;
		return join(pqt_parent, pfk);
	}

	QTable* join(QTable* pqt_parent, FKey* pfk) {
		QTable* pqt = find(pqt_parent, pfk);
		if (pqt)
			return pqt;

		qtables.emplace_back(pqt_parent, pfk);
		return &qtables.back();
	}

};

#endif // QUERY_H_
