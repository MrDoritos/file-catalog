#include "idManager.h"

idManager::idManager() {
	id = 0;
}

idManager::idManager(int begin) {
	id = begin;
}

int idManager::peekId() {
	return id;
}

int idManager::newId() {
	return id++;
}