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

class PKey
{
public:
	typedef vector<Field*>	Fields;

	Table*		pTable;
	string		name;
	string		rst;
	Fields		fields;

	Field* operator[](Fields::size_type n){
		return fields.at(n);
	};

	PKey() : pTable(NULL){};
	~PKey(){};
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
	PKey	pkey;
	FKeys	fkeys;
	Fields	fields;

public:
	Table() {};
	~Table(){};

//Operations
	bool Find(Field* pf);
	Field* GetField(int n);
	Field* GetField(const char* name);
	FKey* GetFKey(const char* name);
	FKey* GetFKey(PKey* pRef);
	PKey* GetPKey(){return &pkey;};
	operator PKey*(){if(!this) return NULL; return &pkey;};
	operator char*(){if(!this) return NULL; return name;};

	Field* GetKeyField(int n){return pkey[n];}
	int    GetKeyFieldCount(){return pkey.fields.size();}

};


#endif /* TABLE_H_ */
