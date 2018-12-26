#pragma once
#include <string.h>
#include "jba.h"
#include "sha.h"

class file {
public:
file(std::string* name) {
//Initialize lists
discs = jaggedbitarray();
tags = jaggedbitarray();
hash = new sha256();

this->name = name;
id = -1;
}
file(const char* text, int id) {
//Initialize lists
discs = jaggedbitarray();
tags = jaggedbitarray();
hash = new sha256();

this->id = id;
this->name = new std::string(text);
}
file(const char* text) {
//Initialize lists
discs = jaggedbitarray();
tags = jaggedbitarray();
hash = new sha256();

this->id = -1;
this->name = new std::string(text);
}

file(std::string* name, int id) {
//Initialize lists
discs = jaggedbitarray();
tags = jaggedbitarray();
hash = new sha256();

this->name = name;
this->id = id;
}

file(std::string* name, int id, sha256* hash) {
discs = jaggedbitarray();
tags = jaggedbitarray();

this->hash = hash;
this->name = name;
this->id = id;
}

//Add
void addtag(int id) { tags.add(id); }
void adddisc(int id) { discs.add(id); }
//Remove 
void removetag(int id) { tags.remove(id); }
void removedisc(int id) { discs.remove(id); }
//Exists
bool tagexists(int id) { return tags.exists(id); }
bool discexists(int id) { return discs.exists(id); }

sha256* hash;
std::string* name;
int id;
jaggedbitarray discs;
jaggedbitarray tags;
};
