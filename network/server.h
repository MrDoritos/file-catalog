#include "packet.h"
#include "tcplistener.h"
#include "tcpsocketclient.h"
#include "client.h"

#define CLIENT_MAX 5 //Should be the same as the backlog on the listener

namespace fc {
	class server {
		public:		 
		server() {}
		
		int start() {
			int err;
			err = listener.sockbind(4100);
			if (err < 0)
				return err;
			err = listener.socklisten();
			if (err < 0)
				return err;
			
		}
		
		private:
		void server_loop() {
			
		}		
		
		static void client_loop(server_client& s_client) {
			
		}
		
		class server_client : fc::client {
			public:
			server_client(fc::server* server, fc::client* client) 
				: fc::client(client)
				{
					
				}
		}
				
		protected:
		void addUser() {
			activeUsers++;
		}
		void subtractUser() {
			activeUsers--;
		}
		tcplistener listener;
		fc::client clients[CLIENT_MAX];
		int activeUsers;
	}
};

#undef CLIENT_MAX