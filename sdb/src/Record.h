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
STD_TYPEDEFS(RKey)
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
		s_dirty = 1, s_null = 2, s_modified = 4, s_hidden = 8
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
	RFields		pRFields;	// Src
	Query*		pQuery;		//Trg
	QFields		pQFields;	//Trg

	RKey(QTable* pqt, Record* pRecSrc);
	virtual ~RKey(){};

	void Get(char* str);
	void SetIdentity();
	uint GetCount(){return pRFields.size();};

	bool IsPrimary();
	bool IsNull();
	void SetNull();

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
	typedef RKeyVectorOwner RKeys;

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
		auto it=rfieldmap.find(pqf);
		return it != rfieldmap.end() ? *it : createRField(pqf);
	}

	RField* getRField(string f){
		QField* pqf = pQuery->getQField(f);
		return getRField(pqf);
	}

	void New();
	void Load();
	void Save();
	void Refresh(RKey* prk);

	RKey* GetRKey(QTable* pqt = NULL);
	RKey* Record::GetRKey(QTable* pqt)
	{
		if(!pqt)
			pqt = pQuery->pQTable;
	/*	else
			pqt = pqt->GetFirstChild();
	*/	for(size_t i = 0; i < pRKeys.size(); i++)
		{
			if(*pRKeys[i] == pqt)
				return pRKeys[i];
		}
		pRKeys.push_back(new RKey(pqt, this));
		if(state == s_dummy && state != s_prepare)
			AssistLoad();
		return pRKeys.back();
	}

};

#endif /* RECORD_H_ */
