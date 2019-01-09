#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include "atoi.h"
#include "console.h"
#include "idmanager.h"
#include "file.h"
#include "tag.h"
#include "tagmanager.h"
#include "bitarray.h"
#include "jba.h"
#include "ioa.h"
#include "atoh.h"
#include "cursesgui.h"

#include "sha.h"
#include "cindex.h"
#include "database.h"
#include "tcpclient.h"
#include "tcplistener.h"
#include "writer.h"
#include "base64encodedecode.h"
#include "paramparser.h"

#define NOID_ERR 50
#define NONAME_ERR 51
#define INVALID_ARGS_ERR 52
#define NULL_ERR 53
#define VOIDID 54
#define NOFILE 55

using namespace std;

//Global variables
bool changesmade = false;
cindex _index;
int _argc;
char** _argv;

//Forward function declarations
void perror(int err);
int load(char* path, cindex& index);
int save(char* path, cindex& index);
void printtag(int id);
void printtag(tag* tag);
void printtags(jaggedbitarray* tags);
void printtags();
void printfiles();
void printdiscs();
void printdisc(int id);
void printdisc(disc* disc);
void printfile(int id);
void printfile(file* file);
void printhash(sha256* hash);
void printstatus(int status);
void processfile(params& params);
void list(params& params);
void hbar(int width);
void hbar();

int main(int argc, char** argv) {
console::bindioctl();
_argc = argc;
_argv = argv;
params params;
parse(params, argc, argv);
load("index.tdb", _index);
//_index.listfiles();
//_index.listtags();
if (BASE_HAS(FILE))
	processfile(params);
else if (BASE_HAS(LIST))
	list(params);

//_index.listfiles();
//_index.listtags();

if (changesmade)
	save("index.tdb", _index);
return 0;
}

void list(params& params) {
if (RET_HAS(FILE))
	printfiles();
if (RET_HAS(TAG))
	printtags();
if (RET_HAS(DISC))
	printdiscs();
}

void printtag(int id) {
tag* tag;

}
void printtag(tag* tag) {

}
void printtags(jaggedbitarray *tags) {
tag *tag;
cout << "Tags:";
for (int b = tags->getnext(-1); b != -1; b = tags->getnext(b)) {
	if ((tag = _index.gettag(b)) != nullptr) {
	cout << " " << SETREDBG << SETBLACKFG << *tag->text << SETWHITEFG << SETBLACKBG;
	} else {
	perror(NULL_ERR);
	}
}
cout << endl;
}
void printdisc(int id) {
disc* disc;

}
void printdisc(disc* disc) {
hbar();
file *_file;
cout << "[" << disc->id << "] " << *disc->name << endl;
printstatus(disc->status);
printtags(&disc->tags);
cout << "Files: ";
for (int i = disc->getnextfile(-1); i != -1; i++) {
	if ((_file = _index.getfile(i)) != nullptr) {
		cout << SETBLUEBG << SETGREENFG << "[" << _file->id << "] " << *_file->name << " ";
	} else {
		perror(NULL_ERR);
	}
}
hbar();
}
void printhash(sha256* hash) {
if (hash->ishashed()) {
	//string hashs = string(hash->hash, 32);
	cout << "Hash: " << SETGREENBG << SETBLACKFG << atoh(hash->hash, 32) << SETWHITEFG << SETBLACKBG << endl;
} else {
	cout << "Hash: " << SETREDBG << "No hash!" << SETBLACKBG << endl;
}
}
void printstatus(int status) {
if (status == AVAILABLE) {
	cout << "Status: " << SETCYANBG << "Available" << SETBLACKBG << endl;
} else {
	cout << "Status: " << SETREDBG << "Missing" << SETBLACKBG << endl;
}
}
void printfile(int id) {
file* file;
file = _index.getfile(id);
if (file != nullptr) {
	printfile(file);
} else {
	perror(NULL_ERR);
}
}
void printfile(file* file) {
hbar();
cout << "[" << file->id << "] " << *file->name << endl;
printstatus(_index.getstatus(file));
printhash(file->hash);
printtags(&file->tags);
hbar();
}

void printfiles() {
file* _file;
for (int i = _index.getnextfile(-1); i != -1; i = _index.getnextfile(i))
	if ((_file = _index.getfile(i)) != nullptr)
		printfile(_file);
}
void printdiscs() {
disc* _disc;
for (int i = _index.getnextdisc(-1); i != -1; i = _index.getnextdisc(i))
	if ((_disc = _index.getdisc(i)) != nullptr)
		printdisc(_disc);
}

void printtags() {
printtags(&_index.tags.Ts.available_map);
}

void hbar() {
hbar(console::getconsolewidth());
}
void hbar(int width) {
for (int w = 0; w < width; w++) {
	cout << '=';
}
cout << endl;
}

void processfile(params& params) {
file* _file;
tag* tag;
//Add a tag
if (RET_HAS(TAG) && RET_HAS(ID) && RET_HAS(TAGTEXT)) {
	//See if index contains it
	if (_index.fileexists(params.id)) {
		_file = _index.getfile(params.id);
		if (_file != nullptr) {
			tag = _index.gettag(_argv[params.text]);
			_index.link(_file, tag);
			changesmade = true;
		} else {
			perror(NULL_ERR);
		}
	} else {
		perror(VOIDID);
	}
}
 else if (RET_HAS(DETAG) && RET_HAS(ID) && RET_HAS(TAGTEXT)) {
	//See if index contains the file
	if (_index.fileexists(params.id)) {
		_file = _index.getfile(params.id);
		if (_file != nullptr) {
			if (_index.tagexists(_argv[params.text])) {
				tag = _index.gettag(_argv[params.text]);
				tag->removefile(_file->id);
				_file->removetag(tag->id);
				changesmade = true;
			} else {
				cout << "Didn't have to do anything." << endl;
			}
		} else {
			perror(NULL_ERR);
		}
	} else {
		perror(VOIDID);
	}
}
 else if (RET_HAS(SHOW) && RET_HAS(ID)) {
	//See if index contains the file
	if (_index.fileexists(params.id)) {
		_file = _index.getfile(params.id);
		if (_file != nullptr) {
			printfile(_file);
		} else {
			perror(NULL_ERR);
		}
	} else {
		perror(VOIDID);
	}
}
 else if (RET_HAS(ADD) && RET_HAS(NAME) && RET_HAS(TAGTEXT)) {
	ifstream f(_argv[params.text], std::ios::binary);
	if (f.good()) {
		sha256* hash = new sha256();
		hash->hashfile(f);
		_file = new file(_argv[params.name], hash);
		if (!_index.containsfile(*hash)) {
			_index.addfile(_file);
			changesmade = true;
		} else {
			cout << "Matching file: [" << _index.getfile(*hash)->id << "] '" << *_index.getfile(*hash)->name << "' found" << endl;
		}
	} else {
		perror(NOFILE);
	}
}

}

int load(char* path, cindex& index) {
//Create a file stream
ifstream file;
int err = 0;
//Open file
file.open("index.tdb");
//Create an instance of a binary reader
binreader br = binreader(file);
//Create an instance of a database reader
database db = database(index, br);
//Load the database
db.load();

//Close file
file.close();
return 0;
}

int save(char* path, cindex& index) {
//Create an output file stream
ofstream file;
int err = 0;
//Open file
file.open("index.tdb");
//Create an instance of a binary writer
binwriter bw = binwriter(file);
//Create an instance of a database writer
database db = database(index, bw);
//Save the database
db.save();

//Close file
file.close();
return 0;
}

void perror(int err) {
switch (err) {
case NONAME_ERR:
cout << "No name provided!" << endl;
break;
case NOID_ERR:
cout << "No Id provided!" << endl;
break;
case NULL_ERR:
cout << "Null object error thrown" << endl;
break;
case VOIDID:
cout << "Id provided doesn't have an object" << endl;
break;
case NOFILE:
cout << "File does not exist, or you miss the proper permissions" << endl;
break;
default:
cout << "Unknown error (" << err << ") has occured" << endl;
break;
}
}
