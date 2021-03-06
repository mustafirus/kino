/*
 * MyDb.cpp
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 *      недописаны бинд параметров
 */

#include "stdx.h"
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
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)))
		throw 1;

	field_count = mysql_stmt_field_count(stmt);
	param_count = mysql_stmt_param_count(stmt);

	if(field_count){
		fields  = new MYSQL_BIND[field_count];
		is_null = new my_bool[field_count];
		length  = new unsigned long[field_count];
		memset(fields,  0, param_count * sizeof(fields[1])); /* zero the structures */
		memset(is_null, 0, param_count * sizeof(is_null[1])); /* zero the structures */
		memset(length,  0, param_count * sizeof(length[1])); /* zero the structures */
	}
	if(param_count){
		params  = new MYSQL_BIND[param_count];
		memset(params, 0, param_count * sizeof(params[1])); /* zero the structures */
	}
}
MyDb::Stmt::~Stmt() {
	delete[] fields;
	delete[] is_null;
	delete[] length;
	delete[] params;
	mysql_stmt_close(stmt);
}

void MyDb::Stmt::bind(RFields& rf) {
	rfields = rf;
	for(size_t i=0; i<rfields.size(); ++i){

		fields[i].buffer_type = MYSQL_TYPE_STRING;
		fields[i].buffer = rfields[i]->GetBuf();
		fields[i].buffer_length = rfields[i]->GetLen();
		fields[i].is_unsigned = 0;
		fields[i].is_null = &is_null[i];
		fields[i].length = &length[i];

	}

	if (mysql_stmt_bind_result(stmt, fields) != 0) throw 1;
}

void MyDb::Stmt::param(RKey* prk) {
	///RFields& rf = *prk;
	RFields rf;
	for(size_t i=0; i < rf.size(); i++)
	{
		fields[i].buffer_type = MYSQL_TYPE_STRING;
		fields[i].buffer = rf[i]->GetBuf();
		fields[i].buffer_length = rf[i]->GetLen();
		fields[i].is_unsigned = 0;
//		fields[i].is_null = &is_null[i]; rf[i]->state == RField::s_null; // как дуплить нулевые фелды
	}
}

void MyDb::Stmt::param(RSField* prf) {
}
void MyDb::Stmt::param(RField* prf) {
}
void MyDb::Stmt::execute() {
	if (mysql_stmt_execute(stmt) != 0) throw 1;
	for(size_t i=0; i<rfields.size(); ++i){
		rfields[i]->SetData(is_null[i]);
	}
}
void MyDb::Stmt::fetch() {
	if(mysql_stmt_fetch(stmt)!=0) throw 1;
}
void MyDb::Stmt::release() {
	if(mysql_stmt_free_result(stmt)!=0) throw 1; ; /* deallocate result set */
	if(mysql_stmt_reset(stmt)!=0) throw 1;
	rfields.clear();
	Database::Stmt::release();
}

