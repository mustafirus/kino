/*
 * Form.h
 *
 *  Created on: 5 июня 2013
 *      Author: golubev
 */

#ifndef FORM_H_
#define FORM_H_

class Form {
	xsltStylesheetPtr cur;
	xmlDocPtr doc;
public:
	Form();
	virtual ~Form();
	void trans(){
		const char* zzz;
		xmlDocPtr res = xsltApplyStylesheet(cur, doc, &zzz);
		xsltSaveResultToFile(stdout, res, cur);
	}
};

#endif /* FORM_H_ */
