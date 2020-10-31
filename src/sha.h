#pragma once
#include "shatwofivesix.h"

struct sha256 {
	sha256();
	sha256(char *hash);
	
	int hashFile(std::string &path);
	int hashFile(std::ifstream &f);
	int hashFile(const char *path);
	
	bool equals(sha256 *cmp);
	bool equals(sha256 &cmp);
	
	bool isHashed();
	char* getHash();
	
	void setHash(char *hash);
	
	char hash[32];
	bool hashed;
};