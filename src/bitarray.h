#pragma once
#include <cstddef>

typedef size_t bitarray_t;

class bitarray {
	public:
	bitarray();
	
	void remove(int i);
	void add(int i);
	bool exists(int i);
	int getCapacity();
	
	static const int blocksize;
	
	private:
	void realloc(size_t blocks);
	
	int allocated_blocks;
	bitarray_t *map;
};