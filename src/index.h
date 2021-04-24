#pragma once
#include <string>

#include "tag.h"
#include "archive.h"
#include "file.h"
#include "objectHandler.h"

#define __index cindex

//Safe to say, index can now be stripped of previous bloat
class __index {
	public:
	//Binding functions. These are necessary for forward and reverse lookup
	//If these functions are not called, I cannot guarrantee functionality
	void bind(tag *tag, file *file);
	void bind(file *file, tag *tag);
	
	//Shortcut
	void bind(const char *text, file *file); 
	void bind(file *file, const char *text);
	
	void bind(tag *tag, archive *archive);
	void bind(archive *archive, tag *tag);
	
	void bind(archive *archive, file *file);
	void bind(file *file, archive *archive);
	
	//Special functionality
	
	//Retrieve an existing tag, or create one if it doesn't exist
	tag* getTag(const char *text);
	tag* getTag(std::string &text);
	tag* getTag(std::string *text);
	
	//Create a tag
	tag* createTag(const char *text);
	tag* createTag(std::string &text);
	tag* createTag(std::string *text);
	
	//Not necessarily a registry, more of a handler, but functions more as a registry
	objectHandler<tag> tagRegistry;
	objectHandler<file> fileRegistry;
	objectHandler<archive> archiveRegistry;
};
