#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <deque>
#include <unordered_map>
#include <memory>
#include <vector>
using namespace std;
//#include "hlpdefs.h"
//#define ASSERT assert
//#define DWORD unsigned

//typedef ptrdiff_t HSTMT,HENV,HDBC;
/*
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
#define BEGIN_CRITICAL_SECTION
#define END_CRITICAL_SECTION
*/
template<class T>
class vector_ptr_owner : public vector<T*>{
	~vector_ptr_owner(){

		for (size_type i=0, max = size(); i < max; ++i){
			delete operator[](i);
		}

	}
};

typedef vector_ptr_owner vecown;
