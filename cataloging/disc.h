#include <string.h>
#include "jba.h"
#include "file.h"

//Same thing as file.h, for now
#define MISSING 0
#define AVAILABLE 1

#pragma once

class disc {
public:
disc(std::string *name, int id) {
this->id = id;
this->name = name;
this->status = 0;
}
disc(std::string *name) {
this->name = name;
id = -1;
this->status = 0;
}
disc(const char* name) {
this->name = new std::string(name);
this->id = -1;
this->status = 0;
}
disc(const char* name, int id) {
this->name = new std::string(name);
this->id = id;
this->status = 0;
}
//+Status
disc(std::string *name, int id, int status) {
this->id = id;
this->name = name;
this->status = status;
}
/*
disc(std::string *name, int status) {
this->name = name;
id = -1;
this->status = status;
}
*/
/*
disc(const char* name, int status) {
this->name = new std::string(name);
this->id = -1;
this->status = status;
}
*/
disc(const char* name, int id, int status) {
this->name = new std::string(name);
this->id = id;
this->status = status;
}


void addfile(file *fil) {
files.add(fil->id);
}
void addtag(tag *tg) {
tags.add(tg->id);
}

int getnextfile(int last) { return files.getnext(last); }
int getnexttag(int last) { return tags.getnext(last); }

int id;

std::string* name;

jaggedbitarray files;
jaggedbitarray tags;

int status;

};
