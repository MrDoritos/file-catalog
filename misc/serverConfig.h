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
int load(std::ostream& file) override {
std::cout <<"Here" <<std::endl;
}
int save(std::istream& file) override {

}
void defaultConfig() override {

}
};
