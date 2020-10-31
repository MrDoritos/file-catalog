#pragma once
#include <iterator>

#include "jaggedbitarray.h"

typedef size_t intobjectarray_t;

#define IOA_BLOCKOF(x) (x / blocksize)
#define IOA_INDEXOF(x) (x % blocksize)

template<class T>
class intobjectarray {
public:
	class iterator {
		public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		
		iterator(int _index, intobjectarray *_ioa) : ptr_(_ioa->get(_index)),ioa(_ioa),index(_index) {}
		
		self_type operator++() {			
			self_type i = *this;
			index = ioa->getNext(index);
			ptr_ = ioa->get(index);
			return i;
		}
		self_type operator++(int junk) { 
			index = ioa->getNext(index);
			ptr_ = ioa->get(index);
			return *this; 
		}
		pointer operator*() {
			return ptr_; 
		}
		pointer operator->() {
			return ptr_; 
		}
		reference operator&() {
			return ptr_;
		}
		bool operator==(const self_type& rhs) { return index == rhs.index; }
		bool operator!=(const self_type& rhs) { return index != rhs.index; }
		
		private:
		int index;
		pointer ptr_;
		intobjectarray *ioa;		
	};
	
	friend class iterator;
	
	iterator begin() {
		return iterator(getNext(-1), this);
	}
	
	iterator end() {
		return iterator(-1, this);
	}

	intobjectarray() {
		
	}
	
	intobjectarray(size_t blocksize) {
		this->blocksize = (blocksize > 0 ? blocksize : 2);
		map = new T**[1];
		map[0] = new T*[blocksize];
		allocated_blocks = 1;
		allocmap.add(0);
		available_map = jaggedbitarray();
	}

	int count() {
		int cnt = 0;
		for (int i = getNext(-1); i != -1; i = getNext(i)) {
			cnt++;
		}
		return cnt;
	}

	T* add(T* t, int pos) {
		if (allocmap.exists(IOA_BLOCKOF(pos))) {
			map[getIndex(pos)][IOA_INDEXOF(pos)] = t;
			available_map.add(pos);
		} else {
			alloc(IOA_BLOCKOF(pos));
			add(t, pos);
		}
	}
	
	bool exists(int pos) {
		return (available_map.exists(pos));
	}
	
	T* get(int pos) {
		if (available_map.exists(pos)) {
			return map[getIndex(pos)][IOA_INDEXOF(pos)];
		} else {
			return 0ULL;
		}
	}
	
	void remove(int pos) {
		available_map.remove(pos);
	}
	
	void alloc(int blocknum) {
		if (allocmap.exists(blocknum)) 
			return;
			
		T*** newmap = new T**[++allocated_blocks];
		
		int cur, relblk, curnewblk;
		cur = -1;
		relblk = 0;
		curnewblk = 0;
		
		allocmap.add(blocknum);

		while ((cur = getNextAlloc(cur)) != -1) {
			if (cur != blocknum) {
				newmap[curnewblk++] = map[relblk++];
			} else {
				newmap[curnewblk++] = new T*[blocksize];
			}
		}
		
		delete map;
		map = newmap;
	}
	
	int getIndex(int i) {
		if (!allocmap.exists(IOA_BLOCKOF(i))) 
			return -1;
		
		int block = IOA_BLOCKOF(i);

		int iter = 0;
		int curblock = 0;

		while (curblock != block && (curblock = getNextAlloc(curblock)) != -1) {
			iter++; 
		}
		
		return iter;
	}

	int getNextAlloc(int last) {
		return (allocmap.exists(last + 1) ? last + 1 : (allocmap.getCapacity() < (last + 1) ? -1 : getNextAlloc(last + 1)));
	}

	int getNext(int last) {
		return available_map.getNext(last);
	}

	int allocated_blocks;
	bitarray allocmap;
	jaggedbitarray available_map;
	intobjectarray_t blocksize;
	T*** map;
};