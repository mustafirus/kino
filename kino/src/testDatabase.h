/*
 * testDatabase.h
 *
 *  Created on: 18 апр. 2013
 *      Author: golubev
 */

#ifndef TESTDATABASE_H_
#define TESTDATABASE_H_

#include "Database.h"
void testDB();
class testDatabase: public Database {
public:
	class Stmt : public Database::Stmt
	{
	public:
		Stmt(){};
		virtual ~Stmt(){};

		virtual void bind(int col, RField* prf){};
		virtual void param(RKey* prk){};
		virtual void param(RSField* prf){};
		virtual void param(RField* prf){};
		virtual void execute(){};
	};
	testDatabase();
	virtual ~testDatabase();
	virtual Stmt* create(const char* sql){return new Stmt();};



	virtual void CheckData(RField* prf){};
	virtual DbCursor* GetCursor(const char* stmt, int maxfr){};
	virtual void ExecDirect(const char* str){};
	virtual DbStmt* Prepare(const char* str){};
	virtual void Set(DbStmt* pst){};
	virtual void Exec(){};
	virtual void ExecFDirect(const char* str, ...){};
	virtual void GetData(int icol, int& data){};
	virtual void GetData(int icol, char*& data){};
	virtual void GetData(int icol, char& data){};
	virtual void GetData(int icol, bool& b){};
	virtual void GetData(int icol, char* data, int num){};
	virtual void* GetIndicator(int rows){};
	virtual Field::Type Convert(const char* frombuf, char* tobuf, Field::Type from, Field::Type to){};
	virtual void Bind(RFields& rf){};
	virtual void GetInfo(TABLEINFO* pti){};

	virtual void Bind(int col, RField* prf){};
	virtual void Bind(int col, char* buf, int len, int* pi, Field::Type type = Field::Char){};

//	virtual void Bind(RKey* prk){};
	virtual void BindParameter(/*int num, */int len, char* buf, unsigned short* pindicator){};
	virtual void BindParameter(/*int num, */int* par){};
	virtual void BindParameter(RKey* prk){};
	virtual void BindParameter(RSField* prf){};
	virtual void BindParameter(RField* prf){};

	virtual bool Read(){};
	virtual void Flush(){};
	virtual void FlushEx(){};
	virtual int  GetIdentity(){};
	virtual bool ExecProc(const char* name, int id, int& newid){};
	virtual bool ExecProc(const char * name, int id, char* str, int slen){};
private:
	virtual int Export(const char* tablename, const char * filename){};
};

#endif /* TESTDATABASE_H_ */
