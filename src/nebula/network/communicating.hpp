#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <galaxy/network/communicating.hpp>

#include <nebula/config.hpp>

namespace neb
{
	namespace network
	{
		class communicating: virtual public gal::network::communicating
		{
			public:
				communicating(neb::app_s, int);
				void	process(gal::network::message::shared_t);

				neb::app_w	app_;
		};
	}
}

#endif







