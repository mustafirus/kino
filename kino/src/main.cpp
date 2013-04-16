/*
 * main.cpp
 *
 *  Created on: 13 апр. 2013
 *      Author: golubev
 */
#include "stdx.h"
#include <unistd.h>
#include <iostream>
#include "Action.h"
#include "Record.h"
#include "OdbcDataBase.h"
#include "Dict.h"


int main() {
    try {
    	const char *dsn="";
    	const char *duser="";
    	const char *dpass="";
    	const char *user="";
    	const char *pass="";
    	Action::pAction = new Action;
    	Record::pDict = new Dict(new OdbcDataBase (dsn, duser, dpass));
    	Record::pDB = new OdbcDataBase("kino", user, pass);
    	while(!Record::pDict->Ready())
    		sleep(5000);

    	// Do somthing here

    	delete Record::pDB;
    	delete Record::pDict;
    	delete Action::pAction;
    } catch(...) {
        std::cerr << "aaaaaaaaa....boom" << std::endl;
    }
    return EXIT_SUCCESS;
}
