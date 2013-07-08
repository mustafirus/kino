/*
 * Record.h
 *
 *  Created on: 6 июля 2013
 *      Author: golubev
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "Query.h"

STD_TYPEDEFS2(RField,QField*)
STD_TYPEDEFS2(RKey,QTable*)
class Record;

template<class T>
class State {
	char data;
public:
	State(char c = 0) : data(c) {}
	bool operator==(T f) {	return (data & f) > 0;	}
	bool operator!=(T f) {	return !(data & f);		}
	void operator=(T f) {	data |= f;				}
	void operator/=(T f) {	data &= ~f;				}
};

class RField {

public:
	QField* pQField;
	void* buf;
	Record* pRec;

	enum Flag {
		s_dirty = 1, s_modified = 2, s_null = 4, s_hidden = 8
	};
	State<Flag> state;


public:

	RField(QField* pqf, Record* pr) :
		pQField(pqf),
		pRec(pr),
		state(s_dirty && s_hidden){
		buf	= malloc(getBufLen());
	}

	virtual ~RField(){
		free(buf);
	}

	void* getBuf() {
		state /= s_null;
		return buf;
	}
	size_t getBufLen(){
		return pQField->pField->buflen;
	}

	RKey* getRKey() {
//		return pRec->getRKey(pQField->pQTable);
		return NULL;
	}

	bool isNull() {return state == s_null;}
	void setNull() { state = s_null; state /= s_dirty; setModified(); }
	void setModified(){
		 state = s_modified;
		 pRec->setModified();
	}
	bool isModified(){
		 return state == s_modified;
	}
	bool isDirty(){
		 return state == s_dirty;
	}

	void Delete(){
/*
		if(ro())
		{
			RKey* prk = pRec->GetRKey(*this);
			state = s_modified;
			state = s_null;
			v++;
			pRec->SetModified();
			prk->SetNull();
			pRec->Refresh(prk);
		}else
		{
			state = s_null;
			state = s_modified;
			state = s_data;
			v++;
		}
*/
	}
};

class RKey
{
public:/// For Link
	typedef RFieldVector RFields;
	typedef QFieldVector QFields;
	QTable*		pQTable;	//Src
	RFields		rFields;	// Src
	Query*		pQuery;		//Trg
	QFields		qFields;	//Trg

	RKey(QTable* pqt, Record* pRecSrc);
	virtual ~RKey(){};

	void Get(char* str);
	void SetIdentity();
	uint GetCount(){return rFields.size();};

	bool isPrimary(){
		return pQTable->isMaster();
	}

	bool isNull(){
		for( auto prf : rFields){
			if(prf->isNull())
				return true;
		}
		return false;
	}
	void SetNull(){
		for( auto prf : rFields){
			prf->setNull();
		}
	}


/*
	void Select(SqlStmt& str);
	void Delete(SqlStmt& str);
	void SrcSelect(SqlStmt& str);
	void Update(SqlStmt& str);
	void Refresh(SqlStmt& str);

*/

	RKey& operator=(RKey& rk);


};


class Record {
public:
	typedef RFieldVectorOwner RFields;
	typedef RKeyMapOwner RKeys;

	enum Flag {
		s_dirty = 1, s_modified = 4
	};
	State<Flag> state;

	Query*		pQuery;
	RFields		rfields;
	RFieldMap	rfieldmap;

	RKey*	pPRKey;
	RKeys	pRKeys;

protected:
	Record();
public:
	Record(RKey* rkey);
	virtual ~Record();

	RField* createRField(QField* pqf)
	{
		RField* prf = new RField(pqf, this);
		rfields.push_back(RFieldPtr(prf));
		rfieldmap.emplace(pqf,prf);
		state = s_dirty;
		return prf;
	}
	RField* getRField(QField* pqf){
		auto it = rfieldmap.find(pqf);
		return it != rfieldmap.end() ? it->second :  createRField(pqf);
	}

	RField* getRField(string f){
		QField* pqf = pQuery->getQField(f);
		return getRField(pqf);
	}

	void New();
	void Load();
	void Save();
	void Refresh(RKey* prk);

	RKey* GetRKey(QTable* pqt = NULL) {
		if(!pqt)
			pqt = pQuery->pQTable;

		auto it = pRKeys.find(pqt);
		if(it != pRKeys.end())
			return it->second.get();
		RKey* prk = new RKey(pqt, this);
		pRKeys.emplace(pqt, RKeyPtr(prk));
		if(state == s_dirty)
			Load(); // need to optimize request to load only RKey fields without joins
					// implement temp instance of Record to load this fields
		return prk;
	}

};

#endif /* RECORD_H_ */
