#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <gal/network/communicating.h>

namespace neb
{
	class app;
	namespace network
	{
		class communicating: virtual public gal::network::communicating
		{
			public:
				communicating(int);
				void	process(gal::network::message::shared_t);

				std::weak_ptr<neb::app>	app_;
		};
	}
}

#endif
