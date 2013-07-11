// Query.cpp: implementation of the Query class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "Query.h"
Query::Queries Query::queries;

string QField::alias(){
	return pQTable->alias;
}
