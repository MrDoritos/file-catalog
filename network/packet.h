#include "tcpclient.h"

struct packet {
public:
packet(packet& pck) {
	memcpy(this, &pck, sizeof(packet));
}
packet(packet* pck) {
	memcpy(this, pck, sizeof(packet));
}
packet() {
type = 0;
datalength = 0;
chksum = 0;
}
packet(int type, long datalength, long chksum) {
this->type = type;
this->datalength = datalength;
this->chksum = chksum;
}
int type;
long datalength;
long chksum;
};
