#include <string.h>
#include <iostream>

#define LIST 1
#define ADD 2
#define SHOW 4
#define TAG 8
#define DETAG 16
#define FILE 32
#define DISC 64
#define ID 128
#define SECOND_ID 256
#define TAGTEXT 512
#define NAME 1024

#define BASE_HAS(x) ((params.base & x) == x)
#define RET_HAS(x) ((params.ret & x) == x)

#define INVALID_ARGS 40

struct params {
char base;
int ret;
int name;
int text;
int nums;
int id;
};

int parse(params& param, int argc, char** argv) {
// We got no arguments except for the executable
if (argc < 2) return;
std::string arg;

// Figure out the first argument
/* Should be
 *
 * file
 * disc
 * tag
 * list
 */
arg = std::string(argv[1]);
if (arg == "file") param.base |= FILE;
 else if (arg == "disc") param.base |= DISC;
 else if (arg == "tag") param.base |= TAG;
 else if (arg == "list") param.base |= LIST;
 else return INVALID_ARGS;

// Figure out the rest of the arguments
for (int i = 2; i < argc; i++) {
arg = std::string(argv[i]);

//Add
if (arg == "add") param.ret |= ADD;
//Tag
else if (arg == "tag") param.ret |= TAG;
else if (arg == "detag") param.ret |= DETAG;
//Show
else if (arg == "show") param.ret |= SHOW;
//Id
else if (arg == "-i") {
if (i < argc - 1) {
param.id = -1;
if (atoi(argv[i + 1], &param.id) == 0) {
	param.ret |= ID;
	i++;
}
}
}
//Name
else if (arg == "-n") {
if (atoi(argv[i + 1], &param.id) == 0) {
	param.ret |= NAME;
	param.name = i + 1;
	i++;
}
}
//Text
else
{
param.text = i;
param.ret |= TAGTEXT;
}



}

}
