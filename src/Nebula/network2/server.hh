#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <Nebula/network/server.hh>

#include <Nebula/network2/communicating.hh>

namespace Neb {
	namespace network {
		class server: public gal::network::server {
			public:
				/** @brief ctor.
				 * @param port port
				 */
				server(unsigned short port, int);
				void		callback_accept(int);
		};
	}
}

#endif

