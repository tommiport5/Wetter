/*
 * StringTpl.cpp
 *
 *  Created on: 02.04.2023
 *      Author: Dad
 */

#include "StringTpl.h"
#include <regex>

std::regex pattern("\\$[_a-zA-Z][_0-9a-zA-Z]*");

StringTpl::StringTpl(const std::string &tpl) :_tpl(tpl){
}

StringTpl::~StringTpl() {
	// TODO Auto-generated destructor stub
}

std::string StringTpl::safe_substitute(StringTpl::map_t &&dict) const {
	std::string result = "";
	std::smatch sm;
	size_t cur = 0;
	std::string rem = _tpl;
	while (regex_search(rem, sm, pattern)) {
		result += sm.prefix();
		StringTpl::map_t::const_iterator repl = dict.find(sm.str().substr(1));
		if (repl == dict.end()) {
			result += sm.str();
		} else {
			result += repl->second;
		}
		rem = sm.suffix();
	}
	result += rem;
	return result;
}

std::string StringTpl::safe_substitute(const StringTpl::map_t &cmap) const {
	return safe_substitute(StringTpl::map_t(cmap));
}
