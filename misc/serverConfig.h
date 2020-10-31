#pragma once
#include "config.h"
#include <fstream>
#include <iostream>

class serverConfig
: public config
{
public:
using config::save;
using config::load;
serverConfig(char* path)
:config(path)
{
	defaultConfig();
}
void load(std::istream& file) override {
	
}
void save(std::ostream& file) override {

}
void defaultConfig() override {

}
};
