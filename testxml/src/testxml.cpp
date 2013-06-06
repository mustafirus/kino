//============================================================================
// Name        : testxml.cpp
// Author      : Andrew Golubev
// Version     :
// Copyright   : GPL
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <xercesc/dom/DOM.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

int main(int argc, char* args[]) {

	try {
 		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n";
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return 1;
	}

	const char* xmlFile = "x1.xml";
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(NULL);
    DOMLSParser       *parser = ((DOMImplementationLS*)impl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
//	DOMConfiguration  *config = parser->getDomConfig();

/*
    config->setParameter(XMLUni::fgDOMNamespaces, doNamespaces);
    config->setParameter(XMLUni::fgXercesSchema, doSchema);
    config->setParameter(XMLUni::fgXercesHandleMultipleImports, true);
    config->setParameter(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);
*/


    DOMDocument *doc = 0;

	try {
        doc = parser->parseURI(xmlFile);
        doc->DOMXPathEvaluator();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (...) {
		cout << "Unexpected Exception \n";
		return -1;
	}

	delete parser;
	return 0;
}
