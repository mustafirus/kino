/*
 * FormManager.h
 *
 *  Created on: 5 июня 2013
 *      Author: golubev
 */

#ifndef FORMMANAGER_H_
#define FORMMANAGER_H_
#include <string>
#include "Form.h"
using namespace std;

class FormManager {
	Form* parseForm(const char* name, int id);
public:
	FormManager();
	virtual ~FormManager();
	Form* getForm(string name, int id);
	static FormManager* getSingleton();
};

#endif /* FORMMANAGER_H_ */
