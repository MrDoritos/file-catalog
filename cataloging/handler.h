#pragma once
#include "ioa.h"
#include "tag.h"
#include "idmanager.h"
#include <string.h>

template<class T>
class handler {
public:
//Underlying array of Ts
intobjectarray<T> Ts;
handler() {
Ts = intobjectarray<T>(16);
Tids = idmanager();
}
T* add(T* t) {
t->id = Tids.peekId();
Ts.add(t, Tids.newId());
return t;
}

T* add(T* t, int id) {
Ts.add(t, id);
//Update the idmanager to be above id
Tids.id = (Tids.id > id ? Tids.id : id + 1);
return t;
}
T* add(std::string* text) {
T* nT = new T(text, Tids.peekId());
Ts.add(nT, Tids.newId());
return nT;
}
T* add(std::string* text, int id) {
T* nT = new T(text, id);
Ts.add(nT, id);
return nT;
}
T* get(int id) {
return Ts.get(id);
}
int count() {
return Ts.count();
}
bool exist(int id) {
return Ts.exists(id);
}
void remove(int id) {
Ts.remove(id);
}

//My "iterator"
int getnext(int last) { return Ts.getnext(last); }
private:
//Ids
idmanager Tids;
};
