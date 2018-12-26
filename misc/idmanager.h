#pragma once
class idmanager {
public:
idmanager() {
id = 0;
}
idmanager(int start) {
id = start;
}
int peekId() { return id; }
int newId() { return id++; }
private:
int id;
};
