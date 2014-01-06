#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <gal/network/server.h>

#include <neb/network/communicating.h>

namespace neb
{
	namespace network
	{
		class server: public gal::network::server
		{
			public:
				server(neb::app_shared, unsigned short, int);
				void	callback_accept(int);

				std::weak_ptr<neb::app>		app_;
		};
	}
}

#endif

