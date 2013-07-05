// Table.h: interface for the Table class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TABLE_H_
#define TABLE_H_

class Field
{
public:

	string name;

	Field(string n) : name(n){}
	~Field(){}

};

typedef unique_ptr<Field> FieldPtr;
typedef vector<FieldPtr>  FieldVectorOwner;
typedef unordered_map<string,FieldPtr>  FieldMapOwner;
typedef vector<Field*>  FieldVector;
typedef unordered_map<string,Field*>  FieldMap;

class Table;

class PKey
{
public:
	typedef FieldVector	Fields;

	Table*		pTable;
	Fields		fields;
	string		rst;


//	PKey() : pTable(NULL){};
	PKey(Table* p) : pTable(p){};
	~PKey(){};

	Field* addField(Field* f){
		fields.push_back(f);
		return f;
	}

};

class FKey
{
public:
	typedef FieldVector	Fields;

	Table*		pTable;
	string		name;
	PKey*		pPKey;
	Fields		fields;

	FKey(Table* t, string n, PKey* pk) : pTable(t), name(n), pPKey(pk){};
	~FKey(){};

	Field* addField(Field* f){
		fields.push_back(f);
		return f;
	}

};

typedef unique_ptr<FKey> FKeyPtr;
typedef vector<FKeyPtr>  FKeyVectorOwner;
typedef unordered_map<string,FKeyPtr>  FKeyMapOwner;
typedef vector<FKey*>  FKeyVector;
typedef unordered_map<string,FKey*>  FKeyMap;

//class QTable;

typedef unique_ptr<Table> TablePtr;
typedef vector<TablePtr>  TableVectorOwner;
typedef unordered_map<string,TablePtr>  TableMapOwner;
typedef vector<Table*>  TableVector;
typedef unordered_map<string,Table*>  TableMap;

class Table
{
	public:/// For Link
	typedef FieldMapOwner	Fields;
	typedef FKeyMapOwner	FKeys;
	typedef TableMapOwner	Tables;

	string	name;
	Fields	fields;
	PKey	pkey;
	FKeys	fkeys;

public:
//	Table() {};
	Table(string n) : name(n), pkey(this) {};
	~Table(){};

	operator PKey*(){
		return &pkey;
	}

	Field* addField(string n){
		Field* f = new Field(n);
		fields.emplace(n,FieldPtr(f));
		return f;
	}

	FKey* addFKey(string n, PKey* pk){
		FKey* f = new FKey(this, n, pk);
		fkeys.emplace(n, FKeyPtr(f));
		return f;
	}

	static Tables	tables;
	static Table* addTable(string n){
		Table* t = new Table(n);
		tables.emplace(n,TablePtr(t));
		return t;
	}


	static void init_base_structure(){



		Table* t;
		FKey *fk1, *fk2;
		t = addTable("sdb_tables");
		t->pkey.addField(t->addField("id"));
		t->addField("name");

		t = addTable("sdb_fields");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		t->pkey.addField(t->addField("id"));
		fk1->addField(t->addField("table_id"));
		t->addField("name");

		t = addTable("sdb_pkeys");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		t->pkey.addField(t->addField("id"));
		fk1->addField(t->addField("table_id"));
		t->addField("fieldname");

		t = addTable("sdb_fkeys");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		fk2 = t->addFKey("pkey", *(tables["sdb_pkeys"]));
		t->pkey.addField(t->addField("id"));
		fk1->addField(t->addField("table_id"));
		fk2->addField(t->addField("pkey_id"));
		t->addField("fieldname");

	}
};



#endif /* TABLE_H_ */
