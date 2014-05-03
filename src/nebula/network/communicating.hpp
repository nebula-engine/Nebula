#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <gru/network/communicating.hpp>

#include <nebula/config.hpp>

namespace neb {
	namespace network {
		class communicating: virtual public gal::network::communicating {
			public:
				communicating(neb::app_s, int);
				void	process(boost::shared_ptr<gal::network::message::shared>);

				neb::app_w	app_;
		};
	}
}

#endif







