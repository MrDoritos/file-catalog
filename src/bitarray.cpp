#include "bitarray.h"

const int bitarray::blocksize = sizeof(bitarray_t) * 8;

bitarray::bitarray() {
	map = new bitarray_t[1];
	map[0] = 0;
	allocated_blocks = 1;
}

void bitarray::remove(int i) {
	if (i < getCapacity()) {
		map[i / blocksize] &= ~(1 << (i % blocksize));
	}	
}

void bitarray::add(int i) {	
	if (i < getCapacity()) {
		map[i / blocksize] |= (1ULL << (i % blocksize));
	} else {
		realloc(((i)/blocksize) + 1);
		add(i);
	}
}

bool bitarray::exists(int i) {
	return (i < getCapacity() && (map[i/blocksize] & (1ULL << (i % blocksize))) != 0);	
}

int bitarray::getCapacity() {
	return allocated_blocks * blocksize;
}

void bitarray::realloc(bitarray_t blocks) {
	if (blocks < allocated_blocks) 
		return;

	bitarray_t *newmap = new bitarray_t[blocks];

	for (int i = 0; i < blocks; i++)
		newmap[i] = 0ULL;	
		
	for (int i = 0; i < allocated_blocks; i++)
		newmap[i] = map[i];

	allocated_blocks = blocks;

	delete map;

	map = newmap;
}