#pragma once

struct idManager {
	idManager();
	idManager(int begin);
	
	int peekId();
	int newId();
	
	int id;
};