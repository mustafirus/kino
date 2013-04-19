/*
 * MyDb.cpp
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#include "stdx.h"
#include "mysql/mysql.h"
#include "MyDb.h"
#include "RField.h"
////////////////////////////////////////////////////////////
///// MyDb
////////////////////////////////////////////////////////////

MyDb::MyDb() {
	conn = mysql_init(NULL);
	if (!conn)
		throw 1;

	conn = mysql_real_connect(conn, "10.99.3.4", "root", "cdvfbg1q", "test", 0,
			NULL, 0);
	if (!conn)
		throw 1;
}

MyDb::~MyDb() {
	mysql_close(conn);
}

Database::Stmt* MyDb::create(const char* sql) {
	return new Stmt(mysql_stmt_init(conn), sql);
}
////////////////////////////////////////////////////////////
///// Stmt
////////////////////////////////////////////////////////////

MyDb::Stmt::Stmt(MYSQL_STMT* st, const char* sql) :
	stmt(st) {
	unsigned long type;
	type = (unsigned long) CURSOR_TYPE_READ_ONLY;
	if (mysql_stmt_attr_set(stmt, STMT_ATTR_CURSOR_TYPE, (void*) &type))
		throw 1;
	/* ... check return value ... */
	/* ... check return value ... */
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
		throw 1;
}
MyDb::Stmt::~Stmt() {
}

void MyDb::Stmt::bind(int col, RField* prf) {
	MYSQL_BIND result[30];
	result[col].buffer_type = MYSQL_TYPE_STRING;
	result[col].buffer = prf->GetBuf();
	result[col].buffer_length = prf->GetLen();
	result[col].is_unsigned = 0;
	result[col].is_null = &is_null[0];
	result[col].length = 0;
}
void MyDb::Stmt::param(RKey* prk) {
}
void MyDb::Stmt::param(RSField* prf) {
}
void MyDb::Stmt::param(RField* prf) {
}
void MyDb::Stmt::execute() {
}
void MyDb::Stmt::release() {
}

