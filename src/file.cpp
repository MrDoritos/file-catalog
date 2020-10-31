#include "file.h"

file::file() {
	id = -1;
}

file::file(std::string *name, int id = -1) {
	this->name = name->c_str();
	this->id = id;
}

file::file(std::string &name, int id = -1)
:file(&name, id) {
	
}

file::file(const char *name, int id = -1) {
	this->name = name;
	this->id = id;
}