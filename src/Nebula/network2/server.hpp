#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <Nebula/network/server.hpp>

#include <Nebula/network2/communicating.hpp>

namespace Neb {
	namespace network {
		class server: public gal::network::server {
			public:
				server(Neb::app_w, unsigned short, int);
				void	callback_accept(int);

				Neb::app_w		app_;
		};
	}
}

#endif

