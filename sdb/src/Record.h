/*
 * Record.h
 *
 *  Created on: 6 июля 2013
 *      Author: golubev
 */

#ifndef RECORD_H_
#define RECORD_H_

#include "Query.h"

class Record;

class RField {

public:
	QField* pQField;


	char* buf;
	RField* pPRField;
	Record* pRec;
	void* pind;
//	char		attr;
	char v;
	enum {
		b_none, b_native, b_foreign
	} buf_attrib;

	enum Flag {
		s_data = 1, s_null = 2, s_new = 3, s_modified = 4, s_hidden = 8
	};
	class State {
		char data;
	public:
		State() {	data = s_hidden;	}
		bool operator==(Flag f) {	return (data & f) > 0;	}
		bool operator!=(Flag f) {	return !(data & f);		}
		void operator=(Flag f) {	data |= f;				}
		void operator/=(Flag f) {	data &= ~f;				}
	};
	State state;

	RField();

public:

	RField(QField* pqf, Record* pr, RField* prf = NULL);
	virtual ~RField();

//	enum Attribute{Hidden = 1, ReadOnly = 2};

	virtual char* GetBuf() {
		state /= s_null;
		return buf;
	}
	int GetLen();
	virtual operator const char*();
	operator Record*() {
		return pRec;
	}

	/*	bool	IsData(){return state == s_data;};
	 void	SetNull(){v++; state = s_null;};
	 bool	IsNull(){return state == s_null;};
	 bool	IsModified(){return state == s_modified;};
	 void	show(bool s = true){if(s) state /= s_hidden; else state = s_hidden;};
	 */
	void SetDefault();
	void SetData(bool null = false);
	void SetModified() {
		v++;
		if (*buf == 0)
			state = s_null;
		state = s_modified;
		pRec->SetModified();
	}
	;
	bool ro();
	bool hidden() {
		return state == s_hidden;
	}
	;
	char ver() {
		return v;
	}
	;
	void* GetIndicator() {
		return pind;
	}
	;

// SQL strings
	void Refresh(SqlStmt& str) {
		pQField->Refresh(str);
	}
	;

	void Delete();
};

class Record {
public:
	Record() {
		// TODO Auto-generated constructor stub

	}
	virtual ~Record() {
		// TODO Auto-generated destructor stub
	}
};

#endif /* RECORD_H_ */
