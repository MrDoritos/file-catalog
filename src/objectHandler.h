#pragma once
#include "intobjectarray.h"
#include "idManager.h"
#include <iterator>

template<typename T>
class objectHandler {
	//I may implement iterators as part of the base functionality in intobjectarray and jaggedbitarray, but it is unlikely that I will want to iterate through them directly
	public:
	class iterator {
		public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(int _index, objectHandler *_objHandler) : ptr_(_objHandler->get(_index)),objHandler(_objHandler) {
			index = _index;
		}
		//_objHandler->Ts.getNext(-1)
		self_type operator++() {			
			self_type i = *this;
			index = objHandler->Ts.getNext(index);
			ptr_ = objHandler->get(index);
			return i;
		}
		self_type operator++(int junk) { 
			index = objHandler->Ts.getNext(index);
			ptr_ = objHandler->get(index);
			return *this; 
		}
		/*
		reference operator*() {
			return *ptr_; 
		}
		pointer operator->() {
			return ptr_; 
		}
		*/		
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
		objectHandler<T> *objHandler;
	};
	friend class iterator;
	
	class const_iterator {
		
	};

	iterator begin() {
		return iterator(Ts.getNext(-1), this);
	}
	
	iterator end() {
		//int last;
		//(last = i) != -2 should always be true
		//for (int i = Ts.getNext(-1); i != -1 && (last = i) != -2; i = Ts.getNext(i));
		return iterator(-1, this);
	}

	//Begin objectHandler
	public:
	objectHandler():objectHandler(256) {
		
	}
	
	objectHandler(size_t blocksize) {
		Ts = intobjectarray<T>(blocksize);
	}
	
	T* add(T *t) {
		t->id = Tids.peekId();
		Ts.add(t, Tids.newId());
		return t;
	}
	
	T* add(T &t) {
		return add(&t);
	}
	
	T* get(int id) {
		return Ts.get(id);
	}
	
	int getNext(int i) {
		return Ts.getNext(i);
	}
	
	int count() {
		return Ts.count();
	}
	
	bool exists(int id) {
		return Ts.exists(id);
	}
	
	bool exists(T* t) {
		return exists(t->id);
	}
	
	bool exists(T &t) {
		return exists(&t);
	}
	
	bool existsByReference(T &t) {
		return existsByReference(&t);
	}
	
	bool existsByReference(T *t) {
		for (auto *single_t : this)
			if (single_t == t)
				return true;
		return false;
	}
	
	intobjectarray<T> Ts;
	idManager Tids;
};