#include "fc_packet.h"
#include "packet.h"
#include "tcpsocketclient.h"
#include "tcplistener.h"
#include "tcpclient.h"

class networker {
public:
	networker(tcpclient& client)
	:client(&client)
	{
		bytesToRead = 0;
	}
	bool getpacket(packet* packet) {
		if (bytesToRead)
			return true;
		char header[20];
		if (getHeader(header))
			return true;
		packet pkt;
		pkt.chksum = *(long*)&header[0];
		pkt.type = *(int*)&header[8];
		pkt.datalength = *(long*)&header[12];
		
		bytesToRead = pkt.datalength;
		if (bytesToRead)
			headerReady = true;
		*packet = packet(pkt);
		
		return false;
	}
	
private:
	long bytesToRead;
	bool headerReady;
	bool dataReady;
	bool isBroken() {
		return client->sockread(nullptr,0) == -1;
	}
	bool getHeader(char header[20]) {
		return client->sockread(header, 20) == -1;
	}
	
	char header[20];
	const tcpclient* client;
};
