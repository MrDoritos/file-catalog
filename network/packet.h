#include "tcpclient.h"

class packet {
protected:
packet() {}
public:
virtual void write(tcpclient& net) = 0
virtual void read(tcpclient& net) = 0
}