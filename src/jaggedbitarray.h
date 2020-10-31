#pragma once
#include <iterator>

#include "bitarray.h"

typedef size_t jaggedbitarray_t;

#define BLOCKSIZE (sizeof(jaggedbitarray_t) * 8)
#define BLOCKOF(x) (x / (BLOCKSIZE))

class jaggedbitarray {
	public:
	class iterator {
		public:
		typedef iterator self_type;
		typedef jaggedbitarray_t value_type;
		typedef jaggedbitarray_t& reference;
		typedef jaggedbitarray_t* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		
		iterator(int _index, jaggedbitarray *_jba);		
		self_type operator++();
		self_type operator++(int junk);
		pointer operator*();
		pointer operator->();
		//reference operator&();
		bool operator==(const self_type& rhs);
		bool operator!=(const self_type& rhs);
		
		private:
		jaggedbitarray_t index;
		pointer ptr_;
		jaggedbitarray *jba;
	};
	
	friend class iterator;	
	iterator begin();	
	iterator end();
	
	public:
	jaggedbitarray();
	int count();
	void add(int i);
	void remove(int i);
	bool exists(int i);
	void alloc(int blocknum);
	int getIndex(int i);
	int getNextAlloc(int last);
	int getNext(int last);
	
	private:	
	jaggedbitarray_t *map;
	int allocated_blocks;
	bitarray allocmap;
};