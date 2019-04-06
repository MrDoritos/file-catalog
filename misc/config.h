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
		save(file);
		return 0;
	}
	int load() {
		load(_configPath);
	}
	int load(char* path) {
		std::ifstream file(path);
		if (!file.is_open())
			return 1;
		load(file);
		return 0;
	}
	virtual void save(std::ostream& file) = 0;
	virtual void load(std::istream& file) = 0;
	virtual void defaultConfig() = 0;
	private:
	char* _configPath;
};
