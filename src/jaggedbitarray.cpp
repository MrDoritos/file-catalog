#include "jaggedbitarray.h"

//iterator

jaggedbitarray::iterator::iterator(int _index, jaggedbitarray *_jba) : index(_index),ptr_(&index),jba(_jba) {}

jaggedbitarray::iterator::self_type jaggedbitarray::iterator::operator++() {			
	jaggedbitarray::iterator::self_type i = *this;
	index = jba->getNext(index);
	//ptr_ = jba->get(index);
	ptr_ = &index;
	return i;
}
jaggedbitarray::iterator::self_type jaggedbitarray::iterator::operator++(int junk) { 
	index = jba->getNext(index);
	//ptr_ = jba->get(index);
	ptr_ = &index;
	return *this; 
}
jaggedbitarray::iterator::pointer jaggedbitarray::iterator::operator*() {
	return ptr_; 
}
jaggedbitarray::iterator::pointer jaggedbitarray::iterator::operator->() {
	return ptr_; 
}
/*
jaggedbitarray::iterator::reference jaggedbitarray::iterator::operator&() {
	return ptr_;
}
*/
bool jaggedbitarray::iterator::operator==(const self_type& rhs) { return index == rhs.index; }
bool jaggedbitarray::iterator::operator!=(const self_type& rhs) { return index != rhs.index; }

//jaggedbitarray

jaggedbitarray::iterator jaggedbitarray::begin() {
	return jaggedbitarray::iterator(getNext(-1), this);
}

jaggedbitarray::iterator jaggedbitarray::end() {
	return jaggedbitarray::iterator(-1, this);
}

jaggedbitarray::jaggedbitarray() {
	allocmap.add(0);
	allocated_blocks = 1;
	map = new jaggedbitarray_t[1];
	map[0] = 0ULL;
}

int jaggedbitarray::count() {
	int cnt = 0;
	for (int i = getNext(-1); i != -1; i = getNext(i))
		cnt++;
	return cnt;
}

void jaggedbitarray::add(int i) {
	if (allocmap.exists(BLOCKOF(i))) {
		int index = getIndex(i);
		map[index] |= (1ULL << (i % BLOCKSIZE));
	} else {
		alloc(BLOCKOF(i));
		add(i);
	}
}

void jaggedbitarray::remove(int i) {
	if (allocmap.exists(BLOCKOF(i))) {
		int index = getIndex(i);
		map[index] &= ~(1ULL << (i % BLOCKSIZE));
	}	
}

bool jaggedbitarray::exists(int i) {
	if (allocmap.exists(BLOCKOF(i))) {
		int index = getIndex(i);
		return ((map[index] & (1ULL << (i % BLOCKSIZE))) != 0);
	} else {
		return false;
	}
}

void jaggedbitarray::alloc(int blocknum) {
	if (allocmap.exists(blocknum)) 
		return;
	
	jaggedbitarray_t *newmap = new jaggedbitarray_t[++allocated_blocks];
	
	int cur = -1;
	int relblk = 0;
	int curnewblk = 0;
	
	allocmap.add(blocknum);

	while ((cur = getNextAlloc(cur)) != -1) {
		if (cur != blocknum) {
			newmap[curnewblk++] = map[relblk++];
		} else {
			newmap[curnewblk++] = 0ULL;
		}
	}
	
	delete map;
	map = newmap;
}

int jaggedbitarray::getIndex(int i) {
	int block = BLOCKOF(i);

	if (allocmap.exists(block)) {
		int iter = 0;
		int curblock = 0;
		
		while (curblock != block && (curblock = getNextAlloc(curblock)) != -1) { 
			iter++;
		}
		
		return iter;
	} else {
		return -1;
	}
}

int jaggedbitarray::getNextAlloc(int last) {
	while (true) {
		if (allocmap.exists(++last)) {
			return last;
		} else {
	 		if (allocmap.getCapacity() < (last)) {
	 			return -1;
	 		}
	 	}
	}
}

int jaggedbitarray::getNext(int last) {
	if (last == -1) {
		if (exists(0)) {
			return 0;
		} else {
			return getNext(0);
		}
	}
	
	int value = last;
	int currentblock = BLOCKOF(value);

	while (true) {
		if (BLOCKOF(value) > currentblock) {
			currentblock = getNextAlloc(currentblock);
		if (currentblock == -1)
			return -1;
		} else {
			value++;
			if (allocmap.exists(BLOCKOF(value)) && (map[getIndex(value)] & (1ULL << (value % BLOCKSIZE))) != 0) {
				return value;
			}
		}
	}
}