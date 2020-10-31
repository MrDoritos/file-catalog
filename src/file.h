#pragma once
#include <string.h>

#include "jaggedbitarray.h"

class file {
	public:
	file();
	file(std::string *name, int id = -1);
	file(std::string &name, int id = -1);
	file(const char *name, int id = -1);
	
	int id;
	const char* name;
	
	jaggedbitarray archives;
	jaggedbitarray tags;	
};