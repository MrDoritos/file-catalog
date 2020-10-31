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
void newWriter(binwriter* writer) {
    this->writer = writer;
}
void newReader(binreader* reader) {
    this->reader = reader;
}
int load() {
loadtags();
loadfiles();
loaddiscs();
return 0;
}
int save() {
savetags();
savefiles();
savediscs();
return 0;
}
int savediscindex(disc* _disc) {
writer->writenum(_disc->id);
writer->writestring(_disc->name);
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
sha256* hash = new sha256();
loadhash(*hash);
file* fil = new file(string, id, hash);
index->addfile(fil, id);

long count = reader->getnum();
long n = 0;
for (int i = 0; i < count; i++) {
n = reader->getnum();
index->link(id, n, FILE_TAG);
}
}
// END FILE LOADING

//FILE SAVING
void savefiles() {
long count = index->filecount();
writer->writenum(count);
for (int i = index->getnextfile(-1); i != -1; i = index->getnextfile(i)) {
	savefile(index->getfile(i));
}

}

void savediscfiles(disc* _disc) {
long count = _disc->filecount();
writer->writenum(count);
for (int i = _disc->getnextfile(-1);;);
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

//DISC SAVING

void savediscs() {
long count = index->disccount();
writer->writenum(count);
for (int i = index->getnextdisc(-1); i != -1; i = index->getnextfile(i)) {
	savedisc(index->getdisc(i));
}
}

void savedisc(disc* dis) {
if (dis == 0ULL) return; //Return if we got a nullptr
//ID and NAME
writer->writenum(dis->id);
writer->writestring(dis->name);
savelinks(&dis->tags);
savelinks(&dis->files);
}

// END DISC SAVING

//DISC LOADING

void loaddiscs() {
long count = reader->getnum();
for (int i = 0; i < count; i++) {
loaddisc();
}
}
void loaddisc() {
long id = reader->getnum();
std::string* string = reader->getstring();
disc* dis = new disc(string);
index->adddisc(dis, id);

linkandload(id, &dis->tags, DISC_TAG);
linkandload(id, &dis->files, DISC_FILE);

}
// END DISC LOADING

//TAG-LINK SAVING

void savelinks(jaggedbitarray* tags) {
writer->writenum(tags->count());
for (int i = tags->getnext(-1); i != -1; i = tags->getnext(i)) {
writer->writenum(i);
}
}

// END TAG-LINK SAVING

//LINK LOADING

void loadlinks(jaggedbitarray* loadto) {
long count = reader->getnum();
for (long i = 0; i < count; i++) {
loadto->add(int(reader->getnum()));
}
}

//Loads an array of Ids and links them
void linkandload(int id, jaggedbitarray* a, int type) {
long count = reader->getnum();
int v;
for (long i = 0; i < count; i++) {
a->add((v = int(reader->getnum())));
index->link(id, v, type);
}
}

// END LINK LOADING

//HASH LOADING
void loadhash(sha256& hash) {
char b[32];
char a = 0;
reader->read(&a, 1);
if (a != 0) {
//Hash
reader->read(&b[0], 32);
hash = sha256(b);
} else {
//No hash
hash = sha256();
}
}

// END HASH LOADING

//HASH SAVING
void savehash(sha256* hash) {
char nullb[1] = { '\0' };
char yesb[1] = { 0x01 };
if (hash->ishashed()) {
writer->write((char*)&yesb, 1);
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
