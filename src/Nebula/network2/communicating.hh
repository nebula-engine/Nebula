#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <Nebula/Types.hh>

#include <Nebula/network2/communicating.hh>

namespace Neb {
	namespace network {
		class communicating: virtual public gal::network::communicating {
			public:
				communicating(int);
				void	process(gal::network::message_s);
		};
	}
}

#endif







