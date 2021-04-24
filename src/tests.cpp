#include <stdio.h>
#include <stdlib.h>

//console
#include "console.h"

//file-catalog
#include "sha.h"
#include "bitarray.h"
#include "jaggedbitarray.h"
#include "intobjectarray.h"
#include "objectHandler.h"
#include "tag.h"
#include "file.h"
#include "archive.h"
#include "index.h"

//console-ui
//#include "helperElement.h"
//#include "terminalElement.h"

char __POS2(char x) {
	if (((x & 15) + 48) > 57) {
		return char((x & 15) + 87);
	} else {
		return char((x & 15) + 48);
	}
}

char __POS1(char x) {
	return __POS2((x & 240) >> 4);
}

void atoh(char* buffer, std::string& str) {
	str.clear();
	str.resize(64);
	for (int i = 0, b = 0; i < 32; i++) {
		str[b++] = __POS1(buffer[i]);
		str[b++] = __POS2(buffer[i]);
	}
}

void error(const char* str, int ercode = 1) {
	fprintf(stderr, "Error: %s (%i)", str, ercode);
	exit(ercode);
}

void testHash() {
	sha256 files[3];
	if (files[0].hashFile("textfile1"))
		error("Failed to hash file");
	if (files[1].hashFile("textfile1"))
		error("Failed to hash file");
	if (files[2].hashFile("textfile2"))
		error("Failed to hash file");
	
	printf("file1 == file2 : %s\r\n", files[0].equals(files[1]) ? "True" : "False");
	printf("file2 == file3 : %s\r\n", files[1].equals(files[2]) ? "True" : "False");
	
	std::string filesStr[3];
	for (int i = 0; i < 3; i++)
		atoh(files[i].getHash(), filesStr[i]);
	
	printf("%s - %s - %s\r\n", filesStr[0].c_str(), filesStr[1].c_str(), filesStr[2].c_str());	
}

void testBitArray() {
	bitarray ba;
	ba.add(64);
	ba.add(455);
	
	printf("ba.exists(64) : %s\r\n", ba.exists(64) ? "True" : "False");
	printf("ba.exists(455) : %s\r\n", ba.exists(455) ? "True" : "False");
	printf("ba.exists(69) : %s\r\n", ba.exists(69) ? "True" : "False");
}

void testJaggedBitArray() {
	jaggedbitarray jba;
	jba.add(64);
	jba.add(455);
	
	printf("jba.exists(64) : %s\r\n", jba.exists(64) ? "True" : "False");
	printf("jba.exists(455) : %s\r\n", jba.exists(455) ? "True" : "False");
	printf("jba.exists(69) : %s\r\n", jba.exists(69) ? "True" : "False");
}

void testIntObjectArray() {
	intobjectarray<float> ioa = intobjectarray<float>(8);
	float dat[3] = { 2.0f, 5.0f, 50.0f };
	ioa.add(&dat[0], 1);
	ioa.add(&dat[1], 64);
	ioa.add(&dat[2], 455);
	
	printf("ioa.exists(64) : %s\r\n", ioa.exists(64) ? "True" : "False");
	printf("ioa.exists(455) : %s\r\n", ioa.exists(455) ? "True" : "False");
	printf("ioa.exists(69) : %s\r\n", ioa.exists(69) ? "True" : "False");
	printf("ioa[1] : %f\r\n", *ioa.get(1));
	printf("ioa[64] : %f\r\n", *ioa.get(64));
	printf("ioa[455] : %f\r\n", *ioa.get(455));
}

void testObjectHandler() {
	struct data {
		data(float __float):_float(__float) {}
		float _float;
		int id;
	} dat[6] = { 1.0f, 5.0f, 4.5f, 9.0f, 6.9f, 6.66f };
	objectHandler<data> objHandler(8);
	for (int i = 0; i < 6; i++)
		objHandler.add(dat[i]);
	//printf("objHandler start (manual): %p\r\n", objHandler.get(objHandler.getNext(-1)));
	//int last;
	//for (int i = objHandler.getNext(-1); i != -1 && (last = i) != -2; i = objHandler.getNext(i));	
	//printf("objHandler   end (manual:) %p\r\n", objHandler.get(last));
	//printf("objHandler start: %p\r\n", &objHandler.begin()->_float);
	//printf("objHandler   end: %p\r\n", &objHandler.end()->_float);
	
	printf("objHandler contains:");
	for (auto _data : objHandler)
		printf(" %.2f", _data->_float);
	printf("\r\n");
}

void testTags() {
	const char* apple = "Apple";
	const char* banana = "Banana";
	const char* carrot = "Carrot";
	sum_t sumApple = tag::getSum(apple);
	sum_t sumBanana = tag::getSum(banana);
	sum_t sumCarrot = tag::getSum(carrot);
	
	std::string appleStr("Apple");
	std::string bananaStr("Banana");
	std::string carrotStr("Carrot");
	sum_t sumAppleStr = tag::getSum(appleStr);
	sum_t sumBananaStr = tag::getSum(&bananaStr);
	sum_t sumCarrotStr = tag::getSum(carrotStr);
	
	printf("(%s|%s) : (%i|%i)\r\n", apple, appleStr.c_str(), sumApple, sumAppleStr);
	printf("(%s|%s) : (%i|%i)\r\n", banana, bananaStr.c_str(), sumBanana, sumBananaStr);
	printf("(%s|%s) : (%i|%i)\r\n", carrot, carrotStr.c_str(), sumCarrot, sumCarrotStr);
	
	tag tagApple(apple);
	tag tagBanana(banana);
	tag tagCarrot(carrot);
	tag tagAppleStr(appleStr);
	tag tagBananaStr(bananaStr, 1);
	tag tagCarrotStr(carrotStr);
	
	printf("(%s|%s) : (%i|%i)\r\n", tagApple.text, tagAppleStr.text, tagApple.sum, tagAppleStr.sum);
	printf("(%s|%s) : (%i|%i)\r\n", tagBanana.text, tagBananaStr.text, tagBanana.sum, tagBananaStr.sum);
	printf("(%s|%s) : (%i|%i)\r\n", tagCarrot.text, tagCarrotStr.text, tagCarrot.sum, tagCarrotStr.sum);
}

void testFilesAndArchives() {
	//Declare
	objectHandler<file> files;
	objectHandler<archive> archives;
	objectHandler<tag> tags;

	//Create
	tag tagApple("Food/Apple");
	tag tagFood("Food");
	tag tagBurrito("Food/Burrito");
		
	file fileBurrito("Burrito");
	file fileApple("Apple");
	
	archive foodArchive("Food Archive");

	//Register
	
	tags.add(tagApple);
	tags.add(tagFood);
	tags.add(tagBurrito);
	
	files.add(fileBurrito);
	files.add(fileApple);
	
	archives.add(foodArchive);
	
	//Bind
	fileBurrito.tags.add(tagBurrito.id);
	fileApple.tags.add(tagApple.id);
	tagBurrito.files.add(fileBurrito.id);
	tagApple.files.add(fileApple.id);
	
	foodArchive.tags.add(tagApple.id);
	foodArchive.tags.add(tagBurrito.id);
	foodArchive.tags.add(tagFood.id);
	tagApple.archives.add(foodArchive.id);
	tagBurrito.archives.add(foodArchive.id);
	tagFood.archives.add(foodArchive.id);
	
	foodArchive.files.add(fileBurrito.id);
	foodArchive.files.add(fileApple.id);
	fileBurrito.archives.add(foodArchive.id);
	fileApple.archives.add(foodArchive.id);
	
	//Debug
	for (auto file : files) {
		printf("File: %s\r\n", file->name);
		for (auto tag : file->tags)
			printf("Has tag: %i\r\n", *tag);
		for (auto archive : file->archives)
			printf("Has archive: %i\r\n", *archive);
	}
	for (auto tag : tags) {
		printf("Tag: %s\r\n", tag->text);
		for (auto file : tag->files)
			printf("Has file: %i\r\n", *file);
		for (auto archive : tag->archives)
			printf("Has archive: %i\r\n", *archive);
	}
	for (auto archive : archives) {
		printf("Archive: %s\r\n", archive->name);
		for (auto file : archive->files)
			printf("Has file: %i\r\n", *file);
		for (auto tag : archive->tags)
			printf("Has tag: %i\r\n", *tag);
	}
}

void printTag(tag* tag) {
	printf("Tag text: %s, tag sum: %i, tag id: %i\r\n", tag->text, tag->sum, tag->id);
}

void testIndex() {
	index master;
	tag* tagApple = master.getTag("Apple");
	tag* tagBanana = master.getTag("Banana");
	
	tag* tagAppleStr = master.getTag(&std::string("Apple String"));
	tag* tagBananaStr = master.getTag(&std::string("Banana String"));
	
	tag* tagAppleStrDup = master.getTag(&std::string("Apple"));
	tag* tagBananaStrDup = master.getTag(&std::string("Banana"));
	
	tag* tagAppleSameSum = master.getTag("pAple");
	
	printTag(tagApple);
	printTag(tagBanana);	
	
	printTag(tagAppleStr);
	printTag(tagBananaStr);
	
	printTag(tagAppleStrDup);
	printTag(tagBananaStrDup);
	
	printTag(tagAppleSameSum);
}

//Define DEBUG_TESTS to load tests
#ifdef DEBUG_TESTS
int main() {
	console::cons.~constructor();
	testHash();
	testBitArray();
	testJaggedBitArray();
	testIntObjectArray();
	testObjectHandler();
	testTags();
	testFilesAndArchives();
	testIndex();
	
	/*
	screen wscreen;
	s_screen = &wscreen;
	terminalElement tE;
	wscreen.child->add(&tE);
	tE.setc(0.5f, 0.0f, 0.5f, 0.5f);
	
	std::thread screen_thread((void(*)(screen*))&screen::start, &wscreen);
		
	screen_thread.join();
	*/
	return 0;	
}
#endif