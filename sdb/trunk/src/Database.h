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
	class Stmtpool: public std::deque<Stmt*> {
	public:
		~Stmtpool();
	};
	typedef std::unordered_map<string, Stmtpool> stmtmap;
	stmtmap stm;
protected:
	virtual Stmt* create(string sql)=0;

public:
	class Stmt {
//		friend class Database;
		bool busy;
	public:
		typedef std::vector<RField*> RFields;
		Stmt() :
				busy(true) {
		}
		virtual ~Stmt() {
		}

		virtual void bind(RFields& rf) = 0;
		virtual void param(RKey* prk) = 0;
		virtual void param(RField* prf) = 0;
		virtual void execute() = 0;
		virtual void fetch() = 0;
		virtual void release();

		bool isBusy(){return busy;};
		void setBusy(bool b){busy = b;};
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
