//============================================================================
// Name        : testmysql.cpp
// Author      : Andrew Golubev
// Version     :
// Copyright   : GPL
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdio.h>
#include <functional>
#include <unordered_map>




#include <mysql/mysql.h>
using namespace std;
class stmt{
	int i;
public:
	stmt():i(0){};
	~stmt(){};
};

void zzz(){
	std::unordered_map<string,int> str_map;
	typedef unordered_map<string,int>::iterator iter;
	str_map["zzz"] = 1;
	str_map["aaa"] = 2;
	int z =	str_map["xxx"];
	for (iter i=str_map.begin(); i!=str_map.end();i++) {
	   std::cout << (*i).first << ": " << (*i).second << std::endl;
	}
	std::cout << "z " << z << std::endl;
}


int main() {
zzz();
exit(0);
	MYSQL *conn;
	MYSQL_STMT *stmt;
	const char *sql;

	// Bind variables
	MYSQL_BIND param[1], result[2];

	int f1_pi=1;
	const char *f1_pc="1";
	char f1[30];
	char f2[30];
	memset(f2, 0, sizeof(f2)); /* zero the structures */
	my_bool is_null[2];

	sql = "select f1,f2 from tab where f1 = ?";
	sql = "select f1,f2 from tab";

	// Open Database
	conn = mysql_init(NULL);

	mysql_real_connect(conn, "10.99.3.4", "root", "cdvfbg1q", "test", 0, NULL, 0);

	// Allocate statement handler
	stmt = mysql_stmt_init(conn);

	unsigned long type;
	type = (unsigned long) CURSOR_TYPE_READ_ONLY;
	mysql_stmt_attr_set(stmt, STMT_ATTR_CURSOR_TYPE, (void*) &type);
	/* ... check return value ... */
	/* ... check return value ... */
	if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
		return 0;
	}

/*
	MYSQL_RES * res= mysql_stmt_result_metadata(stmt);
	MYSQL_FIELD *fld = NULL;
	while( (fld = mysql_fetch_field(res)) ){
		continue;
	}
*/

	// Initialize the result column structures
	memset(param, 0, sizeof(param)); /* zero the structures */
	memset(result, 0, sizeof(result)); /* zero the structures */

	// Init param structure
	// Select
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer = (void *) f1_pc;
	param[0].buffer_length = strlen(f1_pc);
	param[0].is_unsigned = 0;
	param[0].is_null = 0;
	param[0].length = 0;

	// Result
	result[0].buffer_type = MYSQL_TYPE_STRING;
	result[0].buffer = (void *) f1;
	result[0].buffer_length = 30;
	result[0].is_unsigned = 0;
	result[0].is_null = &is_null[0];
	result[0].length = 0;

	result[1].buffer_type = MYSQL_TYPE_STRING;
	result[1].buffer = (void *) f2;
	result[1].buffer_length = 30;
	result[1].is_unsigned = 0;
	result[1].is_null = &is_null[1];
	result[1].length = 0;

	// Bind param structure to statement
/*
	if (mysql_stmt_bind_param(stmt, param) != 0) {
		return 0;
	}
*/

	// Bind result
	if (mysql_stmt_bind_result(stmt, result) != 0) {
		return 0;
	}

	// Set bind parameters

	// Execute!!
	if (mysql_stmt_execute(stmt) != 0) {
		return 0;
	}


/*
	if (mysql_stmt_store_result(stmt) != 0) {
		return 0;
	}
*/


	// Init data

	// Fetch
	while(true){
		while(mysql_stmt_fetch(stmt)==0){
			printf("fuck %s %s\n", f1,f2);
		};
	}

	// Deallocate result set
	mysql_stmt_free_result(stmt); /* deallocate result set */

	// Close the statement
	mysql_stmt_close(stmt);

	// Close Database
	mysql_close(conn);

}




