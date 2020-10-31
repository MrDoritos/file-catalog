#include <fstream>
#include <string>
#include <string.h>

#include "sha.h"

sha256::sha256() {
	hashed = false;
}

sha256::sha256(char *hash) {
	memcpy(getHash(), hash, 32);
	hashed = true;
}

int sha256::hashFile(std::string &path) {
	std::ifstream f(path, std::ios::binary);
	return sha256::hashFile(f);
}

int sha256::hashFile(std::ifstream &f) {
	if (!f.is_open())
		return 1;
	picosha2::hash256(f, &hash[0], &hash[32]);
	hashed = true;
	return 0;
}

int sha256::hashFile(const char *path) {
	std::ifstream f(path, std::ios::binary);
	return sha256::hashFile(f);
}

bool sha256::equals(sha256 *cmp) {
	return  (isHashed() && cmp->isHashed()) &&
			(memcmp(cmp->getHash(), getHash(), 32) == 0);
}

bool sha256::equals(sha256 &cmp) {
	return equals(&cmp);
}

bool sha256::isHashed() {
	return hashed;
}

char* sha256::getHash() {
	return &hash[0];
}

void sha256::setHash(char *hash) {
	memcpy(getHash(), hash, 32);
	hashed = true;
}