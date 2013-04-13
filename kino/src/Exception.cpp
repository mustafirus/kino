// Exception.cpp: implementation of the Exception class.
//
//////////////////////////////////////////////////////////////////////

#include "stdx.h"
#include "Exception.h"


Exception Exception::ex;

void Exception::printf(DWORD fmt, ...)
{
}

void Exception::Effect()
{
	if(memptr)
	{
		if(pfnfree)
			pfnfree(memptr);
		memptr = NULL;
		pfnfree = NULL;
	}
};

void Exception::printf(char* fmt, char code, ...)
{
}
