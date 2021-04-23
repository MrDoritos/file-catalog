#pragma once
#include <string.h>

#include "sha.h"
#include "jaggedbitarray.h"

class file {
	public:
	file();
	file(std::string *name, int id = -1);
	file(std::string &name, int id = -1);
	file(const char *name, int id = -1);
	
	int id;
	const char* name;
	uint64_t size;
	
	__time64_t date;
	sha256 hash;
	
	jaggedbitarray archives;
	jaggedbitarray tags;	
};