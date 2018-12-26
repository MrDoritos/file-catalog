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
sha256(char* hash) {

this->hash = new char[32];
memcpy(this->hash, hash, 32); // Copy the bytes in case the stack or one buffer is used

hashed = true;
}
int hashfile(std::string path) {
int erno;
std::ifstream f(path, std::ios::binary);
std::vector<unsigned char> s(picosha2::k_digest_size);
picosha2::hash256(f, s.begin(), s.end());
this->hash = new char[32];
for (int i = 0; i < 32; i++)
	hash[i] = s[i];
hashed = true;
}
bool operator==(const sha256 b) {
return matches(&b);
}
bool matches(sha256 *cmp) {
return (hashed && cmp->hashed && memcmp(cmp->hash, hash, 32) == 0);
}
private:
char* hash;
bool hashed;
};
