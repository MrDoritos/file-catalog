#include "packet.h"

namespace fc {
	class client {
		public:
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
	}	
};
