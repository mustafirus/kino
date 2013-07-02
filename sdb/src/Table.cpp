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

