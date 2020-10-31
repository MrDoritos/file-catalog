#include <cstring>
#include "tag.h"

tag::tag() {
	id = -1;
}

tag::tag(const char* _text, int id):tag(_text) {
	this->id = id;
}

tag::tag(std::string &_text, int id):tag(_text) {
	this->id = id;
}

tag::tag(std::string *_text, int id):tag(_text) {
	this->id = id;
}

tag::tag(const char* text) {
	int length = strlen(text);
	
	this->text = new char[length + 1];
	memset(this->text, 0, length + 1);
	
	memcpy(this->text, text, length);
	
	sum = getSum(text, length);
}

tag::tag(std::string &text):tag(&text) {}

tag::tag(std::string *text) {
	int length = text->length();
						
	this->text = new char[length + 1];
	memset(this->text, 0, length + 1);
	
	for (int i = 0; i < length; i++)
		this->text[i] = text->at(i);
	
	sum = getSum(this->text);
}

bool tag::isValid() {
	return id != -1 && this->text != nullptr;
}

void tag::addArchive(int id) {
	archives.add(id);
}

void tag::removeArchive(int id) {
	archives.remove(id);
}

bool tag::archiveExists(int id) {
	return archives.exists(id);
}

void tag::addFile(int id) {
	files.add(id);
}

void tag::removeFile(int id) {
	files.remove(id);
}

bool tag::fileExists(int id) {
	return files.exists(id);
}

sum_t tag::getSum() {
	return getSum(text);
}

sum_t tag::getSum(std::string &text) {
	return getSum(&text);
}

sum_t tag::getSum(std::string *text) {
	int length = text->length();
	sum_t sum = 0u;
	
	for (int i = 0; i < length; ++i)
		sum += sum_t(text->at(i));
	
	return sum;
}

sum_t tag::getSum(const char* text) {
	return getSum(text, strlen(text));
}

sum_t tag::getSum(const char* text, int length) {
	sum_t sum = 0u;
	
	for (int i = 0; i < length; ++i)
		sum += sum_t(text[i]);
	
	return sum;
}