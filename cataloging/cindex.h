#pragma once
#include "tagmanager.h"
#include "tag.h"
#include "idmanager.h"
#include "file.h"
#include "disc.h"
#include "ioa.h"
#include "handler.h"
#include <iostream>

#define FILE_TAG 0
#define DISC_TAG 1
#define FILE_DISC 2

class cindex {
public:
cindex() {
tags = handler<tag>();
files = handler<file>();
discs = handler<disc>();
}
//ADD
file* addfile(file* fil) {
return files.add(fil);
}
file* addfile(file* fil, int id) {
return files.add(fil, id);
}
disc* adddisc(disc* dis) {
return discs.add(dis);
}
tag* addtag(tag* tg) {
return tags.add(tg);
}
tag* addtag(const char* text) {
std::string* string = new std::string(text);
tag* tg = new tag(string);
return tags.add(tg);
}
tag* addtag(const char* text, int length) {
std::string* string = new std::string(text, length);
tag* tg = new tag(string);
return tags.add(tg);
}
tag* gettag(const char* text) {
int length = 0;
int pos = 0;
int match = -1;
tag *tg;
char b;
std::string str = string(text);
int sum = tag::chksum(str);
for (int i = tags.getnext(-1); i != -1; i = tags.getnext(i)) {
tg = tags.get(i);
if (tg != 0 && tg->sum == sum && *tg->text == str) { match = i; }
}
if (match != -1) { return gettag(match); } else { return addtag(text); }
}

tag* addtag(tag* tg, int id) {
return tags.add(tg, id);
}
//
int tagcount() { return tags.count(); }
//GET
tag* gettag(int id) {
return tags.get(id);
}

//REMOVE
void removefile(int id) {
files.remove(id);
}
void removedisc(int id) {
discs.remove(id);
}
//Link
void link(file *fil, disc *dis) {
fil->adddisc(dis->id);
dis->addfile(fil->id);
}
void link(file *fil, tag *tag) {
fil->addtag(tag->id);
tag->addfile(fil->id);
}
void link(disc *dis, tag* tag) {
dis->addtag(tag->id);
tag->adddisc(dis->id);
}
void link(int a, int b, int type) {
file* fil;
disc* dis;
tag* tg;

switch (type) {
case FILE_TAG:
//If either object doesn't exist, return
if (!files.exist(a) && !tags.exist(b)) return;
fil = files.get(a);
tg = tags.get(b);
if (fil == 0ULL || tg == 0ULL) return;
link(fil, tg);
break;
case DISC_TAG:
//If either object doesn't exist, return
if (!discs.exist(a) && !tags.exist(b)) return;
dis = discs.get(a);
tg = tags.get(b);
if (dis == 0ULL || tg == 0ULL) return;
link(dis, tg);
break;
case FILE_DISC:
//If either object doesn't exist, return
if (!files.exist(a) && !discs.exist(b)) return;
fil = files.get(a);
dis = discs.get(b);
if (fil == 0ULL || dis == 0ULL) return;
link(fil, dis);
break;
}

}

//Debugging
void listfiles() {
file* fil;
tag* tg;
for (int i = files.getnext(-1); i != -1; i = files.getnext(i)) {
//std::cout << "i:" << i << std::endl;
fil = files.get(i);
std::cout << "------" << std::endl;
std::cout << "|Id  : " << fil->id << std::endl;
std::cout << "|Name: " << *fil->name << std::endl;
std::cout << "|Tags: ";
for (int b = fil->tags.getnext(-1); b != -1; b = fil->tags.getnext(b)) {
if ((tg = gettag(b)) != 0ULL)
std::cout << *tg->text << " ";
}
std::cout << "\r\n------" << std::endl;
}
}
private:
handler<tag> tags;
handler<file> files;
handler<disc> discs;

};
