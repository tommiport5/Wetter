/*
 * StringTpl.h
 *
 *  Created on: 02.04.2023
 *      Author: Dad
 */

#ifndef IMPLEMENTATION_WETTER_STRINGTPL_H_
#define IMPLEMENTATION_WETTER_STRINGTPL_H_

#include <string>
#include <map>
//#include <regex> beware of regex, it might eat your heap
// use this one for our simple regex:
class Simplex {
	enum State {start,outside, first, inside};
	State _state;
	const std::string &_ref;
	std::string::const_iterator scanpos, endofLast, begofMatch, endofMatch;
	bool inFirst(char);
	bool inAll(char);
public:
	Simplex(const std::string &ref)
		: _state(start), _ref(ref),
		  scanpos(ref.begin())
	{};

	const std::string prefix();
	const std::string match();
	const std::string suffix();

	bool search();
};

class StringTpl {
	const std::string _tpl;
public:
	StringTpl(const std::string&);

	typedef std::map<std::string, std::string> map_t;

	std::string safe_substitute(const std::map<std::string, std::string> &cmap) const;
	std::string safe_substitute(std::map<std::string, std::string> &&) const;
};

#endif /* IMPLEMENTATION_WETTER_STRINGTPL_H_ */
