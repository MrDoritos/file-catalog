#pragma once
#include "config.h"
#include <fstream>
#include <iostream>

class serverConfig
: public config
{
public:
serverConfig(char* path)
:config(path)
{
	defaultConfig();
}
void fload(std::istream& file) override {
	
}
void fsave(std::ostream& file) override {

}
void defaultConfig() override {

}
};
