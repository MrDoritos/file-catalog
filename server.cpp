#include "userCountPacket.h"
#include "tcplistener.h"
#include "tcpclient.h"
#include <iostream>
#include "serverConfig.h"

int main() {
serverConfig cnfg("config.txt");
cnfg.load();
/*
tcplistener p = tcplistener();
if (p.sockbind(4100)) {
	std::cout << "Could not bind socket" << std::endl;
	exit(1);
}
p.socklisten();

tcpclient cl;
while (1) {
p.accept_client(cl);
std::cout << "New socket" << std::endl;
cl.cliwrite((void*)"Tu eres feo", 11);
cl.cliclose();
}
*/
return 0;
}
