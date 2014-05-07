#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <Nebula/network2/communicating.hpp>

#include <Nebula/Types.hpp>

namespace Neb {
	namespace network {
		class communicating: virtual public gal::network::communicating {
			public:
				communicating(Neb::app_w, int);
				void	process(boost::shared_ptr<gal::network::message::shared>);

				Neb::app_w	app_;
		};
	}
}

#endif







