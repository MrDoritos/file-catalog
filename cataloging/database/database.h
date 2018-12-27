
#include "writer.h"
#include "reader.h"
#include "cindex.h"
#include "tag.h"
#include "file.h"
#include "disc.h"
#include "sha.h"
#pragma once

//Current format
// Tags:
// 	num: number of tags
// 	array of tags
//	Tag:
//		num: id
//		string: text
//
// Files:
//	num: number of files
//	array of files
//	File:
//		num: id
//		string: name
//		sha: hash
//			SHA:
//				single null byte if no hash or 32 bytes if hashed
//		num: number of tag links
//		array of nums
//
// Discs:
//	num: number of discs
//	array of files
//	Disc:
//		num: id
//		string: name
//		num: number of tag links
//		array of nums
//		num: number of file links
//		array of nums
//
// Index:
//	fuck

class database {
public:
database(cindex &index, binreader &reader) {
this->index = &index;
this->reader = &reader;
}
database(cindex &index, binwriter &writer) {
this->index = &index;
this->writer = &writer;
}
int load() {
loadtags();
loadfiles();
}
int save() {
savetags();
savefiles();
}

cindex* index;
private:
binreader* reader;
binwriter* writer;

//FILE LOADING
void loadfiles() {
long count = reader->getnum();
for (long i = 0; i < count; i++)
	loadfile();
}
void loadfile() {
long id = reader->getnum();
std::string* string = reader->getstring();
sha256* hash;
loadhash(hash);
file* fil = new file(string, id, hash);
index->addfile(fil, id);

long count = reader->getnum();
long n = 0;
for (int i = 0; i < count; i++) {
n = reader->getnum();
index->link(id, i, FILE_TAG);
}
}
// END FILE LOADING

//FILE SAVING
void savefiles() {
long count = index->filecount();
for (int i = index->getnextfile(-1); i != -1; i = index->getnextfile(i)) {
	savefile(index->getfile(i));
}

}

void savefile(file* fil) {
if (fil == 0ULL) return; //Return if we got a nullptr
//ID and NAME
writer->writenum(fil->id);
writer->writestring(fil->name);

savehash(fil->hash); //Save the file's hash
savelinks(&fil->tags); //Save the file's tag links
}

// END FILE SAVING

//TAG-LINK SAVING

void savelinks(jaggedbitarray* tags) {
writer->writenum(tags->count());
for (int i = tags->getnext(-1); i != -1; i = tags->getnext(i)) {
writer->writenum(i);
}
}

// END TAG-LINK SAVING

//HASH LOADING
void loadhash(sha256* hash) {
char b[32];
char a = 0;
reader->read(&a, 1);
if (a != 0) {
//Hash
reader->read(&b[1], 31);
b[0] = a;
hash = new sha256(&*b);
} else {
//No hash
hash = new sha256();
}
}

// END HASH LOADING

//HASH SAVING
void savehash(sha256* hash) {
char nullb[1] = { '\0' };
if (hash->ishashed()) {
writer->write(hash->hash, 32);
} else {
writer->write((char*)&nullb, 1);
}
}
// END HASH SAVING

//TAG LOADING
void loadtags() {
long count = reader->getnum();
for (long i = 0; i < count; i++)
	loadtag();
}
void loadtag() {
long id = reader->getnum();
std::string* s = reader->getstring();
tag* tg = new tag(s, id);
index->addtag(tg, int(id));
}
// END TAG LOADING

//TAG SAVING
void savetags() {
long count = index->tagcount();
writer->writenum(count);
for (long i = index->getnexttag(-1); i != -1; i = index->getnexttag(i)) {
	savetag(index->gettag(i));
}
}
void savetag(tag* t) {
writer->writenum(t->id);
writer->writestring(t->text);
}
// END TAG SAVING

};
