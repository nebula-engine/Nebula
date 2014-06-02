#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <Nebula/Types.hh>

#include <Galaxy-Network/communicating.hpp>

namespace Neb {
	namespace Network {
		class Communicating:
			virtual public gal::network::communicating
		{
			public:
				Communicating(int);
				void	process(gal::network::imessage_s);
		};
	}
}

#endif







