#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <Nebula/Types.hh>

#include <Nebula/network/communicating.hh>

namespace Neb {
	namespace Network {
		class Communicating:
			virtual public gal::network::communicating
		{
			public:
				Communicating(int);
				void	process(gal::network::message_s);
		};
	}
}

#endif







