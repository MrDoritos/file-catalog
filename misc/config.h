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
	int save(char* path) {
		std::ofstream file(path);
		if (!file.is_open())
			return 1;
		fsave(file);
		return 0;
	}
	int load() {
		load(_configPath);
	}
	int load(char* path) {
		std::ifstream file(path);
		if (!file.is_open())
			return 1;
		fload(file);
		return 0;
	}
	virtual void fsave(std::ostream& file) = 0;
	virtual void fload(std::istream& file) = 0;
	virtual void defaultConfig() = 0;
	private:
	char* _configPath;
};
