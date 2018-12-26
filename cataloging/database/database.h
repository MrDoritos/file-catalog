
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

}
int save() {

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
for (long i = 0; i < count; i++) {
	savetag(index->gettag(i));
}
}
void savetag(tag* t) {
writer->writenum(t->id);
writer->writestring(t->text);
}
// END TAG SAVING

};
