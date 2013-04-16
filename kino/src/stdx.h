#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <cstring>
#include <algorithm>
#include <cassert>
#include "hlpdefs.h"
#define ASSERT assert
#define DWORD unsigned

typedef ptrdiff_t HSTMT,HENV,HDBC;
#define RETCODE int
#define SQL_NULL_HSTMT 0
#define SDWORD unsigned short
#define SQL_NTS 0
#define SQL_NULL_DATA 0
struct DATE_STRUCT{
	int day;
	int month;
	int year;
};

#define FUCK_IGNORE_THIS
