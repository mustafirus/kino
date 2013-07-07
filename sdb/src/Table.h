// Table.h: interface for the Table class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TABLE_H_
#define TABLE_H_

STD_TYPEDEFS(Field)
STD_TYPEDEFS(FKey)
STD_TYPEDEFS(Table)


class Field
{
public:
	string	name;
	size_t	buflen;

	Field(string n, size_t b) : name(n), buflen(b){}
	~Field(){}
};

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

	Field* addField(string n, size_t buflen){
		Field* f = new Field(n, buflen);
		fields.emplace(n,FieldPtr(f));
		return f;
	}

	Field* getField(string n){
		return fields.at(n).get();
	}

	FKey* addFKey(string n, PKey* pk){
		FKey* f = new FKey(this, n, pk);
		fkeys.emplace(n, FKeyPtr(f));
		return f;
	}

	FKey* getFKey(string n){
		return fkeys.at(n).get();
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
		t->pkey.addField(t->addField("id", 10));
		t->addField("name", 256);

		t = addTable("sdb_fields");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		t->pkey.addField(t->addField("id", 10));
		fk1->addField(t->addField("table_id", 10));
		t->addField("name", 256);

		t = addTable("sdb_pkeys");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		t->pkey.addField(t->addField("id", 10));
		fk1->addField(t->addField("table_id", 10));
		t->addField("fieldname", 256);

		t = addTable("sdb_fkeys");
		fk1 = t->addFKey("table", *(tables["sdb_tables"]));
		fk2 = t->addFKey("pkey", *(tables["sdb_pkeys"]));
		t->pkey.addField(t->addField("id", 10));
		fk1->addField(t->addField("table_id", 10));
		fk2->addField(t->addField("pkey_id", 10));
		t->addField("fieldname", 256);

	}
};



#endif /* TABLE_H_ */
