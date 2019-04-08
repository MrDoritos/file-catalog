#include "packet.h"

#define USERCOUNT_PACKET 1

namespace fc {
	class fc_packet : protected packet {
		protected:
		fc_packet(int type) {
			this->type = type;
		}
		int type;
	};
}