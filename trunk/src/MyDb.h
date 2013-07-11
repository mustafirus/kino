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
#include "mysql/mysql.h"

class MyDb: public Database {

	MYSQL *conn;

	class Stmt : public Database::Stmt{
		MYSQL_STMT*		stmt;
		unsigned int 	field_count;
		unsigned long	param_count;
		MYSQL_BIND*		fields;
		my_bool*		is_null;
		unsigned long*	length;
		MYSQL_BIND*		params;
		RFields			rfields;

		void bind(RFields& rf);
		void param(RKey* prk);
		void param(RSField* prf);
		void param(RField* prf);
		void execute();
		void fetch();
		void release();

	public:
		Stmt(MYSQL_STMT* st, const char* sql);
		virtual ~Stmt();

	};

	Database::Stmt* create(const char* sql);
public:
	MyDb();
	virtual ~MyDb();
};

#endif /* MYDB_H_ */
