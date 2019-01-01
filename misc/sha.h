#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "shatwofivesix.h"
#pragma once

class sha256 {
public:
sha256() {
hashed = false;
}
//We trust that you use a 32 byte hash
/*
sha256(char* hash) {

this->hash = new char[32];
memcpy(this->hash, hash, 32); // Copy the bytes in case the stack or one buffer is used

hashed = true;
}
*/
sha256(char hash[32]) {
this->hash = new char[32];
for (int i = 0; i < 32; i++)
	this->hash[i] = hash[i];
hashed = true;

}
int hashfile(std::string path) {
int erno = 0;
std::ifstream f(path, std::ios::binary);
std::vector<unsigned char> s(picosha2::k_digest_size);
picosha2::hash256(f, s.begin(), s.end());
this->hash = new char[32];
for (int i = 0; i < 32; i++)
	hash[i] = s[i];
hashed = true;
return erno;
}
int hashfile(ifstream& f) {
int erno = 0;
std::vector<unsigned char> s(picosha2::k_digest_size);
picosha2::hash256(f, s.begin(), s.end());
this->hash = new char[32];
for (int i = 0; i < 32; i++)
	hash[i] = s[i];
hashed = true;
return erno;
}

bool operator==(sha256 b) {
return matches(&b);
}
bool matches(sha256 *cmp) {
return (hashed && cmp->hashed && memcmp(cmp->hash, hash, 32) == 0);
}
bool ishashed() { return (hashed); }
char* hash;
private:
bool hashed;
};
