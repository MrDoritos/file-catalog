#include "packet.h"
#include "tcpclient.h"

namespace fc {
	class client {
		public:
		client() {}
		client(client* cl) {
			this->cli = cl->cli;
		}
		client(tcpclient& cli) {
			this->cli = &cli;
		}
		void send(packet* pck) {
			pck->write(*cli);
		}
		void recieve(packet* pck) {
			pck->read(*cli);
		}
		private:
		tcpclient* cli;		
	};
}
