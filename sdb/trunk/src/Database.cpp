/*
 * Database.cpp
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#include "stdx.h"
#include "Database.h"

Database::Stmtpool::~Stmtpool(){
	while (!empty())
	  {
	    delete back();
	    pop_back();
	  }
};

Database::Stmt* Database::prepare(string sql){
	Stmtpool& sp = stm[sql];
	auto i=sp.begin();
	Stmt* p;
	while(i != sp.end()){
		p = (*i);
		BEGIN_CRITICAL_SECTION
		if(!p->isBusy()){
			p->setBusy(true);
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

