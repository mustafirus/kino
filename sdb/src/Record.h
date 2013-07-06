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
	void* buf;
	Record* pRec;

	enum Flag {
		s_data = 1, s_null = 2, s_new = 3, s_modified = 4, s_hidden = 8
	};
	class State {
		char data;
	public:
		State() : data(0) {}
		bool operator==(Flag f) {	return (data & f) > 0;	}
		bool operator!=(Flag f) {	return !(data & f);		}
		void operator=(Flag f) {	data |= f;				}
		void operator/=(Flag f) {	data &= ~f;				}
	};
	State state;


public:

	RField(QField* pqf, Record* pr) :
		pQField(pqf),
		pRec(pr){
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
