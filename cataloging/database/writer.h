#include <ostream> include <string.h>

class binwriter {
public:
binwriter(std::ostream &stream) {
this->stream = &stream;
}
void writenum(long num) {
int pos = 0; //The current position in buffer
/*
 *	EXAMPLE
 *	|---------------|-------|0--- 4--- 8--- 12--- 16--- 20---|
 *	|Dec. Val	|Flag	|Bits
 *	|0		|No	|0000 0000 ----  ----  ----  ----|
 *	|1		|No	|0000 0001 ----  ----  ----  ----|
 *	|2		|No	|0000 0010 ----  ----  ----  ----|
 *	|127		|No	|0111 1111 ----  ----  ----  ----|
 *	|128		|Yes	|1100 0000 0000  0000  ----  ----|
 *	|255		|Yes	|1111 1111 0100  0000  ----  ----|
 *	|256		|Yes	|1000 0001 0000  0000  ----  ----|
 */

//num = 255
//      1111 1111
long out = num;
char a = 0;
while (1) {
a = out & 127;
//a = 0111 1111 (127)
out >>= 7;
//out = 0000 0001 (1)
if (out > 0) { a |= 128; buffer[pos++] = a; } else { buffer[pos++] = a; break; }
//a = 1111 1111 (255)
}
stream->write(buffer, pos);

}
void writestring(std::string &string) {
long length = string.length();

//Write the size of the string
writenum(length);

//Write the string
//for (int i = 0; i < length; i++) {
//stream->write((char*)(string[i]), 1);
//}
(*stream) << string;

}
void writestring(std::string *string) {
long length = string->length();

//Write the size of the string
writenum(length);

//Write the string
//for (int i = 0; i < length; i++) {
//stream->write((*string)[i], 1);
//}
(*stream) << (*string);

}
private:
char buffer[256];
std::ostream *stream;
};
