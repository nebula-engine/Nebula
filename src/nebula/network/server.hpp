#ifndef __NEBULA_NETWORK_SERVER_H__
#define __NEBULA_NETWORK_SERVER_H__

#include <gru/network/server.hpp>

#include <nebula/network/communicating.hpp>

namespace neb
{
	namespace network
	{
		class server: public gal::network::server
		{
			public:
				server(neb::app_s, unsigned short, int);
				void	callback_accept(int);

				std::weak_ptr<neb::app>		app_;
		};
	}
}

#endif

