#include "tcpclient.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	tcpclient cli;
	uint8_t address[] = {192,168,1,13};
	int r;
	if (r = cli.sockconnect((char*)&address, 4100) < 0) {
		std::cout << "error: " << r << std::endl;
		exit(1);
	}
	char buf[255];
	cli.sockwrite((char*)"qwertyuiopasdfghjklzxcvbnm", 26);
	r = cli.sockread(&buf[0], 255);
	if (r < 0) {
		std::cout << "recieve error" << std::endl;
		exit(r);
	} else {
		std::string str = std::string(&buf[0], r);
		std::cout << "Recieved:\n" << str << std::endl;
	}
	cli.sockclose();
	return 0;
}
