//============================================================================
// Name        : testweb++.cpp
// Author      : Andrew Golubev
// Version     :
// Copyright   : GPL
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>

#include "web++.hpp"

using namespace std;
using namespace WPP;

void web(Request* req, Response* res) {
    cout << req->method << " " << req->path << endl;

    cout << "Headers:" << endl;

    map<string, string>::iterator iter;
    for (iter = req->headers.begin(); iter != req->headers.end(); ++iter) {
        cout << iter->first << " = " << iter->second << endl;
    }

    cout << "Query:" << endl;

    for (iter = req->query.begin(); iter != req->query.end(); ++iter) {
        cout << iter->first << " = " << iter->second << endl;
    }

    cout << "Cookies: " << req->cookies.size() << endl;

    for (iter = req->cookies.begin(); iter != req->cookies.end(); ++iter) {
        cout << iter->first << " = " << iter->second << endl;
    }

    res->body << "HELLO";
}




int main() {
    try {
        cout << "Listening on port 5000" << endl;

        WPP::Server server;
        server.get("/", &web);
        server.get("/zzz", &web);
        server.all("/dir", "./");
        server.start(5000);
    } catch(WPP::Exception e) {
        cerr << "WebServer: " << e.what() << endl;
    }

    return EXIT_SUCCESS;
}
