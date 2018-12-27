#include <string.h>
#include "jba.h"
#include "file.h"
#pragma once

class disc {
public:
disc(std::string *name, int id) {
this->id = id;
this->name = name;
}
disc(std::string *name) {
this->name = name;
id = -1;
}
disc(const char* name) {
this->name = new std::string(name);
this->id = -1;
}
disc(const char* name, int id) {
this->name = new std::string(name);
this->id = id;
}

void addfile(file *fil) {
files.add(fil->id);
}
void addtag(tag *tg) {
tags.add(tg->id);
}

int id;

std::string* name;

jaggedbitarray files;
jaggedbitarray tags;

};
