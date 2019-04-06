#pragma once
#include <iostream>
#include <fstream>

class config {
	public:
	config(char* configPath) {
		this->_configPath = configPath;
	}

	int save() {
		save(_configPath);
	}
	virtual int save(std::ostream& file) {

	}
	int save(char* path) {
		std::ofstream file(path);
		if (!file.is_open())
			return 1;
		return save(file);
	}
	int load() {
		load(_configPath);
	}
	int load(char* path) {
		std::ifstream file(path);
		if (!file.is_open())
			return 1;
		return load(file);
	}
	virtual int load(std::istream& file) {

	}
	virtual void defaultConfig() {

	}
	private:
	char* _configPath;
};
