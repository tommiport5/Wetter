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

class StringTpl {
	std::string _tpl;
public:
	StringTpl(const std::string&);
	virtual ~StringTpl();

  typedef std::map<std::string, std::string> map_t;

	std::string safe_substitute(const std::map<std::string, std::string> &cmap) const;
	std::string safe_substitute(std::map<std::string, std::string> &&) const;
};

#endif /* IMPLEMENTATION_WETTER_STRINGTPL_H_ */
