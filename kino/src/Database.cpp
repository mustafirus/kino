/*
 * Database.cpp
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#include "stdx.h"
#define DATABASE_0X
#include "Database.h"

Database::stmtpool::~stmtpool(){
	while (!empty())
	  {
	    delete back();
	    pop_back();
	  }
};

Database::Stmt* Database::prepare(const char* sql){
	stmtpool& sp = stm[sql];
	stmtpool::iterator i=sp.begin();
	Stmt* p;
	while(i != sp.end()){
		p = (*i);
		BEGIN_CRITICAL_SECTION
		if(!p->busy){
			p->busy = true;
			return p;
		}
		END_CRITICAL_SECTION
	};
	p = create(sql);
	sp.push_back(p);
	return p;
};

void Database::Stmt::release(){
	busy=false;
}

