//============================================================================
// Name        : String2Func.cpp
// Author      : 
// Version     :
// Copyright   : MIT open source license
// Description : Helper class for building servers
//============================================================================
#include "Arduino.h"
#include "ServerWrapper.h"
using namespace std;

#include "local.h"

// simplify the use of std::string instead of String
//const String &String(const std::string &sr) {return String(sr.c_str());};

ServerWrapper::ServerWrapper() :_server(80) {}

ServerWrapper::~ServerWrapper() {
	// TODO Auto-generated destructor stub
}

const string nFound = {
  "File Not Found \n\n"
  "URI: "
};

void ServerWrapper::send(int fc, const char* tp, const std::string &txt) {
  _server.send(fc, tp, txt.c_str());
}

void ServerWrapper::begin() {
  if (MDNS.begin(host)) {
    Serial.println("MDNS responder started");
    _server.onNotFound([this] (){
      send(404, "text/plain", nFound + _server.uri().c_str() + '\n');
    });
    _server.begin();
  }
}

void tunix(const string &wem) {
	Serial.println("Ich will bloß spielen");
}
/*
int demo() {
	s2f.execute("spielen", tunix, "franz");
	s2f.execute("arbeiten",
			[](const char * wem) {
				Serial.print("Arbeiten will ich mit ");Serial.println(wem);
			}, "fritz");
	return 0;
}
*/
