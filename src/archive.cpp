#include "archive.h"

archive::archive() {

}

archive::archive(std::string *name, int id = -1, int status = 0) {
	this->name = name->c_str();
	this->id = id;
	this->status = status;
}
archive::archive(std::string &name, int id = -1, int status = 0)
:archive(&name, id, status) {
	
}

archive::archive(const char *name, int id = -1, int status = 0) {
	this->name = name;
	this->id = id;
	this->status = status;
}