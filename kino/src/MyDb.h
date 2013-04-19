/*
 * MyDb.h
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#ifndef MYDB_H_
#define MYDB_H_

#define DATABASE_0X

#include "Database.h"

class MyDb: public Database {
	typedef struct st_mysql MYSQL; // forward declaration
	typedef struct st_mysql_stmt MYSQL_STMT; // forward declaration

	class Stmt : public Database::Stmt{
		MYSQL_STMT* stmt;
	public:
		Stmt(MYSQL_STMT* st, const char* sql);
		virtual ~Stmt();

		void bind(int col, RField* prf);
		void param(RKey* prk);
		void param(RSField* prf);
		void param(RField* prf);
		void execute();
		void release();
	};
	Database::Stmt* create(const char* sql);
	MYSQL *conn;
public:
	MyDb();
	virtual ~MyDb();
};

#endif /* MYDB_H_ */
