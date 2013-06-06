/*
 * Form.cpp
 *
 *  Created on: 5 июня 2013
 *      Author: golubev
 */

#include "inc.h"
#include "Form.h"

Form::Form() {
	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;
	cur = xsltParseStylesheetFile((const xmlChar *)"");
	doc = xmlParseFile("");

}

Form::~Form() {
	xsltFreeStylesheet(cur);
	//xmlFreeDoc(res);
	xmlFreeDoc(doc);

        xsltCleanupGlobals();
        xmlCleanupParser();
}

