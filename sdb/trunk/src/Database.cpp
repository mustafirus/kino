/*
 * Database.cpp
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#include "stdx.h"
#include "Database.h"


Database::Stmt* Database::prepare(string sql){
	StmtPool & sp = stm[sql];
	for(auto & pst : sp){
		if(pst->lock())
			return pst.get();
	}
	Stmt* p = create(sql);
	sp.push_back(unique_ptr<Stmt>(p));
	return p;
};

void Database::Stmt::release(){
	busy.unlock();
}

