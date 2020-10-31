#pragma once
#include <string>

#include "jaggedbitarray.h"

typedef unsigned short sum_t;

class tag {
	public:
	tag();
	tag(const char* text);
	tag(std::string &text);
	tag(std::string *text);
	tag(const char* text, int id);
	tag(std::string &text, int id);
	tag(std::string *text, int id);
		
	void addArchive(int id);
	void removeArchive(int id);
	bool archiveExists(int id);
	
	void addFile(int id);
	void removeFile(int id);
	bool fileExists(int id);
		
	sum_t getSum();
	static sum_t getSum(std::string &text);
	static sum_t getSum(std::string *text);
	static sum_t getSum(const char* text);
	static sum_t getSum(const char* text, int length);
	
	bool isValid();
		
	jaggedbitarray files;
	jaggedbitarray archives;
	
	char* text; //std::string too many bytes	
	sum_t sum;
	int id;
};