#include <iostream>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include "file.h"
#include "cindex.h"

using namespace std;

int getdir(string dir, vector<char*> &files, bool recursive);
bool getfile(file& file);
void error(const char* erro);
void error();
void error(int errn);
void error(const char* erro, int errn);

int main() {
	vector<char*> files = vector<char*>();
	getdir(string("."), files, false);
	for (auto &d : files)
		printf("File: %s\n", d);
}

int getdir(string dir, vector<char*> &files, bool recursive) {
	DIR* dp;
	struct dirent* dirp;
	if ((dp = opendir(dir.c_str())) == nullptr) {
		error("Opening directory", errno);
		return errno;
	}
	
	while ((dirp = readdir(dp)) != nullptr) {
		int len = strlen(dirp->d_name);
		char* d = new char[len + 1];
		strcpy(d, dirp->d_name);
		files.push_back(d);
	}
	
	closedir(dp);
	return 0;
}

bool getfile(file& file) {


}

void error() {
	error("An error occured");
}

void error(int errn) {
	error("An error occured", errn);
}

void error(const char* erro) {
	error(erro, 1);
}

void error(const char* erro, int errn) {
	printf("%s (%i)\r\n", erro, errn);
	exit(errn);
}
