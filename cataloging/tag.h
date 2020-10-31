#include <string>
#include "jba.h"
#pragma once

class tag {
public:
tag(const char* text, int id) {
this->text = new std::string(text);
this->id = id;
//Initialize the lists
files = jaggedbitarray();
discs = jaggedbitarray();

sum = chksum(this);
}
tag(std::string* text, int id) {
this->text = text;
this->id = id;
//Initialize the lists
files = jaggedbitarray();
discs = jaggedbitarray();

sum = chksum(this);
}
tag(std::string* text) {
id = -1;
this->text = text;
//Initialize the lists
files = jaggedbitarray();
discs = jaggedbitarray();

sum = chksum(this);
}
//Add
void adddisc(int id) { discs.add(id); }
void addfile(int id) { files.add(id); }
//Remove //NOT IMPLEMENTED IN jaggedbitarray.h
void removedisc(int id) { discs.remove(id); }
void removefile(int id) { files.remove(id); }
//Exist
bool discexists(int id) { return discs.exists(id); }
bool fileexists(int id) { return files.exists(id); }

int id;
int sum;
std::string* text;
jaggedbitarray files;
jaggedbitarray discs;
static int chksum(tag* stag) {
int sum = 0;
const char* s = stag->text->c_str();
for (int i = 0; i < stag->text->length(); i++)
	sum += s[i];
return sum;
}
static int chksum(std::string &string) {
int sum = 0;
const char* s = string.c_str();
for (int i = 0; i < string.length(); i++)
	sum += s[i];
return sum;
}
static int chksum(const char* text, int length) {
int sum = 0;
for (int i = 0; i < length; i++)
	sum += text[i];
return sum;
}
};
