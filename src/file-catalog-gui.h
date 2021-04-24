/*
	Holds a singleton state of the whole program
*/

#pragma once
#include "index.h"
#include "screen.h"

#include "helperElement.h"

//Debug message
//_DM("onFrame called?\r\n");
#ifdef DEBUG
	#ifdef __linux__ 
		#define _DM(...) //Can't stderr printf with ncurses
		#define _DB(...)
		#define debugf(...)
	#else
		#define _DM(...) \
			fprintf(stderr, __VA_ARGS__)
		#define _DB(x) \
			fprintf(stderr, "%s\r\n", x)
		#define debugf(...) \
			fprintf(__VA_ARGS__)
		#endif
#else
	#define _DM(...)
	#define _DB(...)
	#define debugf(...)
#endif

struct filecatalog {
	char *indexPath;
	index index;
	element *guiChild;
	screen *wscreen;
	
	static filecatalog *instance;
		
	void parseArgs(int argc, char** argv);
};

//Some elements to test

struct textElement : public helperElement<textElement> {
	textElement(const char *text):textElement(std::string(text)) {}
	textElement(std::string text):helperElement(this) {
		length = text.length();
		this->text = text;
		color = new char[length];
		memset(color, FWHITE | BBLACK, length);
		pos = 0;
	}
	
	void onCreate() override {
		_DB("onCreate TE");
		setc(parent->get());
	}
	
	void setTextColor(char color) {
		setTextColor(0, length, FWHITE | BBLACK);
	}
	
	void setTextColor(int pos, char color) {
		if (pos < length)
			this->color[pos] = color;
	}
	
	void setTextColor(int start, int end, char color) {
		if (end > start - 1)
			return;
		if (end > length - 1)
			return;
		
		memset(this->color + start, color, end - start);
	}
	
	void onUpdate() {
		if (length != text.length()) {
			char *nColor = new char[text.length()];
			for (int i = 0; i < length && i < text.length(); i++)
				nColor[i] = color[i];
			for (int i = length; i < text.length(); i++)
				nColor[i] = FWHITE | BBLACK;
			
			delete color;
			color = nColor;
			
			length = text.length();
		}
		
		int count = getSizeX() * getSizeY();
		if (text.length() > count) {
			//Text is too long for size, we need to scroll
			if (ticks++ % 5 == 0) { //every 500ms
				if (length - ++pos < count)
					pos = -5;
			}
		} else {
			pos = 0;
		}			
	}
	
	void onFrame() {
		_DB("onFrame TE");
		_DB(text.c_str());
		int sx = getSizeX(), sy = getSizeY(), c;
		c = sx * sy;
		int pos = this->pos > 0 ? this->pos : 0;
		debugf(stderr, "%i:%i:%i %i:%i", sx,sy,c,pos,text.length());
		for (int i = 0; i < c && i < text.length() + pos; i++) {
			write(i % sx, i / sx, text[i + pos], color[i + pos]);
		}
	}
	
	int ticks;
	int length, pos;
	bool center, scroll; //not using these yet
	std::string text; //widechar soon
	char* color;
};

struct optionElement : public helperElement<optionElement> {
	optionElement(const char *text, bool selected = false, bool highlighted = false):
	optionElement(std::string(text), selected, highlighted) {}
	optionElement(std::string text, bool selected = false, bool highlighted = false):helperElement(this),text(text) {
		this->text.text.insert(0, "[ ] ");	
		setHighlighted(highlighted);
		setSelected(selected);	
		
		add((element*)&this->text);
	}
	
	void onCreate() {
		_DB("onCreate OE");
		setc(box(0,0,parent->getSizeX(), 1));		
	}
	
	void setHighlighted(bool b) {
		highlighted = b;
		if (b)
			text.setTextColor(FWHITE | BGREEN);
		else 
			text.setTextColor(FWHITE | BBLACK);
	}
	
	void setSelected(bool b) {
		selected = b;
		if (b) 
			text.text[1] = 'x';
		else
			text.text[1] = ' ';
	}
	
	bool selected, highlighted;
	textElement text;
};

struct optionListElement : public helperElement<optionListElement> {
	optionListElement():helperElement(this),options(8) {
		
	}
	
	//optionElement(s) are to be added to this element's child list, as well as this list
	intobjectarray<optionElement*> options;
	
	void onCreate() override {
		_DB("onCreate OLE");
		setc(0.0f,0.0f,0.5f,0.5f);
	}
	
	void addOption(int id, const char* opt) {
		optionElement *option = new optionElement(opt);
		options.add(&option, id); //problematic line
		add(option);
	}
};

struct guiHandler : public helperElement<guiHandler> {
	guiHandler():helperElement(this) {
		
	}
	
	void onCreate() override {
		setc(box(0,0,console::getConsoleWidth(), console::getConsoleHeight()));
	}
	
	void onFrame() override {
		write(0,0,'H', FWHITE | BBLACK);		
	}
};