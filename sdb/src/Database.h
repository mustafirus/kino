/*
 * Database1.h
 *
 *  Redezigned on: 17 апр. 2013
 *      Author: golubev
 */

#ifndef DATABASE_H_
#define DATABASE_H_


class RField;


class DbStmt;
class RSField;
class RKey;

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
		typedef std::vector<RField*> RFields;
		Stmt() : busy(true){
		}
		virtual ~Stmt() {
		}


		virtual void bind(RFields& rf) = 0;
		virtual void param(RKey* prk) = 0;
		virtual void param(RSField* prf) = 0;
		virtual void param(RField* prf) = 0;
		virtual void execute() = 0;
		virtual void fetch() = 0;
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

};
#endif // DATABASE_H_
