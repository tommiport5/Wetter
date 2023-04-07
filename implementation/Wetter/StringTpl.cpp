/*
 * StringTpl.cpp
 *
 *  Created on: 02.04.2023
 *      Author: Dad
 */
#include "StringTpl.h"

StringTpl::StringTpl(const std::string &tpl) :
		_tpl(tpl)
{}


std::string StringTpl::safe_substitute(StringTpl::map_t &&dict) const {
	std::string result = "";
	Simplex sm(_tpl);
	while (sm.search()) {
		result += sm.prefix();
		StringTpl::map_t::const_iterator repl = dict.find(sm.match().substr(1));
		if (repl == dict.end()) {
			result += sm.match();
		} else {
			result += repl->second;
		}
	}
	result += sm.suffix();
	return result;
}

std::string StringTpl::safe_substitute(const StringTpl::map_t &cmap) const {
	return safe_substitute(StringTpl::map_t(cmap));
}

const std::string Simplex::prefix() {
	return std::string(endofLast,begofMatch);
}

const std::string Simplex::match() {
	return std::string(begofMatch, endofMatch);
}

const std::string Simplex::suffix() {
	return std::string(endofLast,_ref.end());
}

bool Simplex::inFirst(char c) {
	return c == '_' ||
			c >='a' && c <='z' ||
			c >= 'A' && c <= 'Z';
}

bool Simplex::inAll(char c) {
	return c >= '0' && c <= '9' || inFirst(c);
}

bool Simplex::search() {
	while (scanpos != _ref.end()) {
		//std::cout << _state << " " << *scanpos << std::endl;
		switch (_state) {
		case start:
			endofLast = scanpos;
			_state = outside;
			break;
		case outside:
			if (*scanpos == '$') {
				begofMatch = scanpos;
				_state = first;
			}
			scanpos ++;
			break;
		case first:
			if (*scanpos == '$') {
			    begofMatch = scanpos;
			    // _state remains first
			} else if (inFirst(*scanpos)) {
				endofMatch = scanpos;
				_state = inside;
			} else {
				_state = outside;
			}
			scanpos++;
			break;
		case inside:
			if (inAll(*scanpos)) {
				scanpos++;
			} else {
				endofMatch = scanpos;
				_state = start;
				return true;
			}
			break;
		}

	}
	endofMatch = _ref.end();
	return false;
}
