#include "packet.h"

#define USERCOUNT_PACKET 1

namespace fc {
	class fc_packet {
		protected:
		fc_packet(int type) {
			this->type = type;
		}
		public:
		int type;
		long chksum;
		long datalength;
		bool readData(void* buffer, size_t count) {
			
		}
		
	};
}
