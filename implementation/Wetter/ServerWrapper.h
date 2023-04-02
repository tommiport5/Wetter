/*
 * ServerWrapper.h
 *
 *  Created on: 31.03.2023
 *      Author: dad
 */

#ifndef SERVERWRAPPER_H_
#define SERVERWRAPPER_H_

#include <string>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class ServerWrapper {
  ESP8266WebServer _server; 
  
public:
	ServerWrapper();
	virtual ~ServerWrapper();

  void begin();
  void handleClient() {_server.handleClient();};
  void send(int, const char*, const std::string &);

	template<class index=std::string, class callable>
	void answer(index ix, callable func) {
    _server.on(ix, [func, this]() {
		  func(this);
    });
	};
};

#endif /* SERVERWRAPPER_H_ */
