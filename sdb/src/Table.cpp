// Table.cpp: implementation of the Table class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "Dict.h"
#include "Field.h"
#include "Table.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Field* Table::GetField(int n)
{
	if(n>=0 && n<fields.GetSize())	return fields[n];
	else return NULL;
}

Field* Table::GetField(const char* name)
{
	for(int i=0; i < fields.GetSize(); i++)
	{
		if(!strcasecmp(fields[i]->name, name))
			return fields[i];
	}
	return NULL;
};

FKey* Table::GetFKey(const char* name)
{
	for(int i = 0; i < pFKeys.GetSize(); i++)
	{
		if(!strcasecmp(name,pFKeys[i]->name))
			return pFKeys[i];
	}
	return NULL;
}

FKey* Table::GetFKey(PKey* pRef)
{
	ASSERT(pRef);
	for(int i = 0; i < pFKeys.GetSize(); i++)
	{
		if(pFKeys[i]->pPKey == pRef)
			return pFKeys[i];
	}
	return NULL;
}

bool Table::Find(Field* pf)
{
	for(int i = 0; i < fields.GetSize(); i++)
		if(fields[i]==pf)
			return true;
		return false;
}

#ifdef _DEBUG
void Table::Dump()
{
	printf("Table %s\n", name);
	mPKey.Dump();
	for(int i = 0; i < pFKeys.GetSize(); i++)
		pFKeys[i]->Dump();

}
void PKey::Dump()
{
	printf("Primary - %s\n", name);
	for(int i = 0; i < fields.size(); i++)
	{
		printf("\t%s\n", fields[i]->name);
	}
}
void FKey::Dump()
{
	printf("Foreign - %s\n", name);
	printf("\tReferences - %s\n", pPKey->name);
	for(int i = 0; i < fields.size(); i++)
	{
		printf("\t%s - %s\n", fields[i]->name, (*pPKey)[i]->name);
	}
}
#endif //_DEBUG
