//#include "userCountPacket.h"
#include "tcplistener.h"
#include "tcpsocketclient.h"
#include <iostream>
#include "serverConfig.h"
#include <string>

int main() {
serverConfig cnfg((char*)"config.txt");

cnfg.load();

tcplistener p = tcplistener();
if (p.sockbind(4100)) {
	std::cout << "Could not bind socket" << std::endl;
	exit(1);
}
p.socklisten();

tcpsocketclient cl;
while (1) {
p.accept_client(cl);
std::cout << "New socket" << std::endl;
cl.sockwrite((void*)"Tu eres feo", 11);
char buf[256];
int r = cl.sockread(&buf, 256);
if (r > 0) {
std::string str(buf, r);
std::cout << str << std::endl;
}
cl.sockclose();
}

return 0;
}
