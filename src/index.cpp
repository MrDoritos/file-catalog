#include "index.h"

void __index::bind(tag *tag, file *file) {
	bind(file, tag);
}
	
void __index::bind(const char *text, file *file) {
	bind(file, text);
}
	
void __index::bind(tag *tag, archive *archive) {
	bind(archive, tag);
}

void __index::bind(archive *archive, file *file) {
	bind(file, archive);
}

void __index::bind(file *file, tag *tag) {
	file->tags.add(tag->id);
	tag->files.add(file->id);
}

void __index::bind(archive *archive, tag *tag) {
	archive->tags.add(tag->id);
	tag->archives.add(archive->id);
}

void __index::bind(file *file, archive *archive) {
	file->archives.add(archive->id);
	archive->files.add(file->id);
}

void __index::bind(file *file, const char *text) {
	bind(file, getTag(text));
}	
	
tag* __index::getTag(const char *text) {
	//TODO Binary search
	int length = strlen(text);
	sum_t sum = tag::getSum(text, length);
	
	//Returns if a matching tag is found in the registry
	for (auto tag : tagRegistry)
		if (tag->sum == sum && tag->isValid()) {
			if (strlen(tag->text) < length)
				continue;
			if (memcmp(tag->text, text, length) == 0)
				return tag;
		}
		
	//If we get here, a matching tag was not found
	return createTag(text);
}

tag* __index::getTag(std::string &text) {
	return getTag(&text);
}

tag* __index::getTag(std::string *text) {
	int length = text->length();
	char strText[length + 1];
	memset(&strText[0], 0, length + 1);
	
	for (int i = 0; i < length; i++)
		strText[i] = text->at(i);
	
	return getTag(&strText[0]);
}
	
tag* __index::createTag(const char *text) {
	//Memory management good
	return tagRegistry.add(new tag(text));
}

tag* __index::createTag(std::string &text) {
	return createTag(&text);
}

tag* __index::createTag(std::string *text) {
	int length = text->length();
	char strText[length + 1];
	memset(&strText[0], 0, length + 1);
	
	for (int i = 0; i < length; i++)
		strText[i] = text->at(i);
	
	return createTag(&strText[0]);
}
