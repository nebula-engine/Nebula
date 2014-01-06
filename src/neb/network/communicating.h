#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <gal/network/communicating.h>

#include <neb/config.h>

namespace neb
{
	namespace network
	{
		class communicating: virtual public gal::network::communicating
		{
			public:
				communicating(neb::app_shared, int);
				void	process(gal::network::message::shared_t);

				std::weak_ptr<neb::app>	app_;
		};
	}
}

#endif







