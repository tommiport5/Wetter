/*
 * main.cpp
 *
 *  Created on: 03.04.2023
 *      Author: Dad
 */

#include <iostream>
#include <map>
#include <utility>
#include "StringTpl.h"
using namespace std;

StringTpl::map_t init {
	{"fritz", "der erste"},
	{"franz", "der zweite"}
};
const StringTpl T1 = StringTpl("Fritz ist $fritz und Franz $franz.");
const StringTpl T2 = StringTpl("Fritz, $fritz gibt Franz $100.");
const StringTpl T3 = StringTpl("Fritz, $fritz gibt Franz $$hundert.");
const StringTpl T4 = StringTpl("Fritz, $fritz gibt Franz $ $hundert.");


const StringTpl::map_t &build_dict() {
	static const StringTpl::map_t built{
		{"fritz", "der grosse"},
		{"franz", "der kleine"}
	};
	return built;
}

// testing the move semantics
StringTpl::map_t &&dyn_build(StringTpl::map_t &_dyn) {
	StringTpl::map_t local;
	local["fritz"] = "der grosse";
	local["klaus"] = "der schnelle";
	local["hundert"] = "100";
	swap(local, _dyn);
	return move(_dyn);
}

int main(int argc, char *argv[]) {
	StringTpl::map_t dyn;
	cout << T1.safe_substitute(init) << endl;
	cout << T1.safe_substitute(build_dict()) << endl;
	cout << T2.safe_substitute(dyn_build(dyn)) << endl;
	cout << T3.safe_substitute(dyn_build(dyn)) << endl;
}

