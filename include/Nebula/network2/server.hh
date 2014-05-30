#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <Nebula/network/server.hh>

#include <Nebula/network2/communicating.hh>

namespace Neb {
	namespace Network {
		class Server: public gal::network::server {
			public:
				/** @brief ctor.
				 * @param port port
				 */
				Server(unsigned short port, int);
				void		callback_accept(int);
		};
	}
}

#endif

