/*
 * main.cpp
 *
 *  Created on: 13 апр. 2013
 *      Author: golubev
 */

int main() {
    try {
    	Action::pAction = new Action;
    	Record::pDict = new Dict(new OdbcDataBase (dsn, duser, dpass));
    	Record::pDB = new OdbcDataBase("kino", user, pass);
    	while(!Record::pDict->Ready())
    		Sleep(5000);

    	// Do somthing here

    	delete Record::pDB;
    	delete Record::pDict;
    	delete Action::pAction;
    } catch(...) {
        cerr << "aaaaaaaaa....boom" << endl;
    }
    return EXIT_SUCCESS;
}
