#include "fc_packet.h"
#include "tcpclient.h"

class userCountPacket : private fc_packet {
	public:
	userCountPacket() :
		fc_packet(USERCOUNT_PACKET)
		{
			userCount = 0;
		}
	void write(tcpclient& cli) override {
		cli.sockwrite((void*)&userCount, 4);
	}
	void read(tcpclient& cli) override {
		cli.sockread((void*)&userCount, 4);
	}
	int getUserCount() {
		return userCount;
	}
	void setUserCount(int cnt) {
		userCount = cnt;
	}
	private:
	int userCount;
};
