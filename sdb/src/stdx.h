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
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

inline queue<string> split(string str, char delim){
	stringstream ss(str);
	string item;
	queue<string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push(item);
    }
    return elems;
}



#define STD_TYPEDEFS2(X,T) class X; \
typedef unique_ptr<X> X##Ptr; \
typedef vector<X##Ptr>  X##VectorOwner; \
typedef unordered_map<T,X##Ptr>  X##MapOwner; \
typedef vector<X*>  X##Vector; \
typedef unordered_map<T,X*>  X##Map;

#define STD_TYPEDEFS(X) STD_TYPEDEFS2(X,string)


