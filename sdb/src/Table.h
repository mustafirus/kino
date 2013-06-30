// Table.h: interface for the Table class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TABLE_H_
#define TABLE_H_

class Field
{
public:
	enum Type{Unknown, Char, TinyInt, SmallInt, Integer, Date, Time, DateTime};

	string name;

	Field();
	~Field();

};

typedef char NAME[30];
typedef char* PNAME;
/*typedef struct NAMEINFO_tag
{
	int		fnum;
	int		pnum;
	PNAME*	names;
}NAMEINFO, *PNAMEINFO;
*/
class PKey
{
public:
	vector<Field*>	Fields;
	Table*		pTable;
	string		name;
	string		rst;
	int			fnum;
	int			pnum;
	Fields		fields;
	NAME*		forms;
	NAME*		procs;

	Field* operator[](int n){
		return fields.at();
		if(n >= 0 && n < fields.size())return fields[n]; else return NULL;
	};
	PKey() : pTable(NULL), name(NULL), capt(NULL), ext(NULL), rst(NULL), style(0), form(0), list(0), 
	fnum(0), pnum(0), forms(NULL), procs(NULL){};
	~PKey(){ifdel((char*)name); ifdel((char*)capt); ifdel((char*)ext); ifdel((char*)rst);
	if (forms) delete[] forms; if(procs) delete[] procs;};

};

class FKey : public PKey
{
public:
	PKey*		pPKey;

	FKey() : pPKey(NULL){};
	~FKey(){};

};

//class QTable;
class Table
{
public:/// For Link
	vecown<Field>	Fields;
	vecown<FKey>	FKeys;

	string	name;
	Fields	fields;
	FKeys	pFKeys;
	PKey	mPKey;

public:
	Table(): name(NULL) {};
	~Table(){};

//Operations
	bool Find(Field* pf);
	Field* GetField(int n);
	Field* GetField(const char* name);
	FKey* GetFKey(const char* name);
	FKey* GetFKey(PKey* pRef);
	PKey* GetPKey(){return &mPKey;};
	operator PKey*(){if(!this) return NULL; return &mPKey;};
	operator char*(){if(!this) return NULL; return name;};

	Field* GetKeyField(int n){return mPKey[n];}
	int    GetKeyFieldCount(){return mPKey.fields.GetSize();}

};


#endif /* TABLE_H_ */
