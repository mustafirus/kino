/*
 * Database1.h
 *
 *  Redezigned on: 17 апр. 2013
 *      Author: golubev
 */

#ifndef DATABASE_H_
#define DATABASE_H_


class RField;
class RSField;
class RKey;

class Database {
public:
	class Stmt;

private:
	typedef deque<unique_ptr<Stmt>> StmtPool;
	typedef unordered_map<string, StmtPool> StmtMap;
	StmtMap stm;
protected:
	virtual Stmt* create(string sql)=0;

public:
	class Stmt {

		mutex busy;
	public:
		typedef RFieldVector RFields;
		Stmt(){
			busy.lock();
		}
		virtual ~Stmt() {
			busy.unlock();
		}
		bool lock(){return busy.try_lock();};
		void unlock(){busy.unlock();};

		virtual void bind(RFields& rf) = 0;
		virtual void param(RKey* prk) = 0;
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

	virtual Stmt* prepare(string sql);
	virtual int get_id() {
		return 0;
	}
	constexpr static Database* pdb = nullptr;

};
#endif // DATABASE_H_
