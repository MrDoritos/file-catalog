#pragma once
#include <string.h>

#include "jaggedbitarray.h"

class archive {
	public:
	archive();
	archive(std::string *name, int id = -1, int status = 0);
	archive(std::string &name, int id = -1, int status = 0);
	archive(const char *name, int id = -1, int status = 0);
	
	int id;
	int status;
	const char* name;
	
	jaggedbitarray files;
	jaggedbitarray tags;	
};