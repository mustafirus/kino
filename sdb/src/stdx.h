#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <sstream>


#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_map>

#include <vector>
#include <map>
#include <memory>

#include <iostream>
using namespace std;
#define ASSERT assert
#define BEGIN_CRITICAL_SECTION
#define END_CRITICAL_SECTION

//#include "hlpdefs.h"
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
*/
/*
template<class T>
class vector_ptr_owner : public vector<T*>{
	~vector_ptr_owner(){

		for (size_type i=0, max = size(); i < max; ++i){
			delete operator[](i);
		}

	}
};

template<class T>
class unordered_map_owner : public std::unordered_map<string, T*>{
	~unordered_map(){

		for (size_type i=0, max = size(); i < max; ++i){
			delete operator[](i);
		}

	}
};

typedef vector_ptr_owner vecown;
*/
inline queue<string> split(string str, char delim){
	stringstream ss(str);
	string item;
	queue<string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push(item);
    }
    return elems;
}
