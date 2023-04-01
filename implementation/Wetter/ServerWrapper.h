/*
 * ServerWrapper.h
 *
 *  Created on: 31.03.2023
 *      Author: dad
 */

#ifndef SERVERWRAPPER_H_
#define SERVERWRAPPER_H_

#include <string>

class ServerWrapper {
public:
	ServerWrapper();
	virtual ~ServerWrapper();

	template<class index=std::string, class callable, class... Ts>
	void execute(index ix, callable func, Ts... args) {
		Serial.print(ix); Serial.println(" will trigger ");
		func(std::forward<decltype(args)>(args)...);
	}
};

#endif /* SERVERWRAPPER_H_ */
