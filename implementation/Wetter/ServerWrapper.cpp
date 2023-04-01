//============================================================================
// Name        : String2Func.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Arduino.h"
#include "ServerWrapper.h"
using namespace std;

ServerWrapper::ServerWrapper() {
	// TODO Auto-generated constructor stub

}

ServerWrapper::~ServerWrapper() {
	// TODO Auto-generated destructor stub
}

ServerWrapper s2f;

void tunix(const char *wem) {
	Serial.println("Ich will bloß spielen");
	Serial.print("und zwar mit "); Serial.println(wem);
}

int demo() {
	s2f.execute("spielen", tunix, "franz");
	s2f.execute("arbeiten",
			[](const char * wem) {
				Serial.print("Arbeiten will ich mit ");Serial.println(wem);
			}, "fritz");
	return 0;
}

