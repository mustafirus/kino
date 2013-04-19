/*
 * Database1.h
 *
 *  Redezigned on: 17 апр. 2013
 *      Author: golubev
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "Field.h"
#include "Set.h"
#include "Defines.h"
#include "DBCursor.h"

class RSField;
class RKey;
class DbStmt {
	char* buf;
public:
	DbStmt(const char* stmt) {
		buf = new char[strlen(stmt) + 1];
		strcpy(buf, stmt);
	}
	virtual ~DbStmt() {
		delete buf;
	}
	operator const char*() {
		return buf;
	}
};
class Database {
public:
	class Stmt;
private:
	typedef std::string string;
	class stmtpool: public std::deque<Stmt*> {
	public:
		~stmtpool();
	};
	typedef std::unordered_map<string, stmtpool> stmtmap;
	stmtmap stm;
protected:
	virtual Stmt* create(const char* sql)=0;

public:
	class Stmt {
		friend class Database;
		bool busy;
	public:
		Stmt() {
		}
		virtual ~Stmt() {
		}

		virtual void bind(int col, RField* prf) = 0;
		virtual void param(RKey* prk) = 0;
		virtual void param(RSField* prf) = 0;
		virtual void param(RField* prf) = 0;
		virtual void execute() = 0;
		virtual void release();
	};
	Database() {
	}
	virtual ~Database() {
	}
	// new design


	virtual Stmt* prepare(const char* sql);
	virtual int get_id() {
		return 0;
	}

#ifndef DATABASE_0X
public:
	virtual void CheckData(RField* prf) = 0;
	virtual DbCursor* GetCursor(const char* stmt, int maxfr) = 0;
	virtual void ExecDirect(const char* str) = 0;
	virtual DbStmt* Prepare(const char* str) = 0;
	virtual void Set(DbStmt* pst) = 0;
	virtual void Exec() = 0;
	virtual void ExecFDirect(const char* str, ...) = 0;
	virtual void GetData(int icol, int& data) = 0;
	virtual void GetData(int icol, char*& data) = 0;
	virtual void GetData(int icol, char& data) = 0;
	virtual void GetData(int icol, bool& b) = 0;
	virtual void GetData(int icol, char* data, int num) = 0;
	virtual void* GetIndicator(int rows) = 0;
	virtual Field::Type Convert(const char* frombuf, char* tobuf,
			Field::Type from, Field::Type to) = 0;
	virtual void Bind(RFields& rf) = 0;
	virtual void GetInfo(TABLEINFO* pti) = 0;

	virtual void Bind(int col, RField* prf) = 0;
	virtual void Bind(int col, char* buf, int len, int* pi, Field::Type type =
			Field::Char) = 0;

	//	virtual void Bind(RKey* prk) = 0;
	virtual void BindParameter(/*int num, */int len, char* buf,
			unsigned short* pindicator) = 0;
	virtual void BindParameter(/*int num, */int* par) = 0;
	virtual void BindParameter(RKey* prk) = 0;
	virtual void BindParameter(RSField* prf) = 0;
	virtual void BindParameter(RField* prf) = 0;

	virtual bool Read() = 0;
	virtual void Flush() = 0;
	virtual void FlushEx() = 0;
	virtual int GetIdentity() = 0;
	virtual bool ExecProc(const char* name, int id, int& newid) = 0;
	virtual bool ExecProc(const char * name, int id, char* str, int slen) = 0;
private:
	virtual int Export(const char* tablename, const char * filename) = 0;

#endif //DATABASE_0X
};

#endif // DATABASE_H_
