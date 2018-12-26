#include <istream>
#include <iostream>

class binreader {
public:
binreader(std::istream &stream) {
this->stream = &stream;
}

long getnum() {
long out = 0;
char a = 0;
int num = 0;
while (1) {
stream->read(&a, 1);

out |= (long(a & 127) << num);
//std::cout << "out:" << out << "0b" << std::bitset<64>(out) << std::endl;
//std::cout << (((unsigned int)a) & 255) << std::endl;
//std::cout << "h:" << (((int)a) & 255) << std::endl;
if ((a & 128) > 0) {

num += 7;
} else {
break;
}



}

return out;
}

std::string* getstring() {
std::string* string = new std::string();
getstring(*string);
return string;
}

void read(char* buffer, int length) {
stream->read(buffer, length);
}

void getstring(std::string &string) {
long length = getnum();
//std::cout << length << std::endl;
char* buffer = new char[length];
stream->read(buffer, length);
string = std::string(buffer, length);
//(*stream) >> string;
}

private:
std::istream *stream;
char buffer[8];
};
